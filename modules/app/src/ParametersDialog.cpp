#include "ParametersDialog.h"
#include "Icons.h"

#include "tsr/doc/DocCommands.h"

#include <QBrush>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QVBoxLayout>

#include <algorithm>
#include <functional>

namespace tsr::app {

namespace {
enum Column { kStar = 0, kParameter, kName, kUnit, kExpression, kValue, kComment };
// Row data, on the Name column.
constexpr int kKindRole = Qt::UserRole;        // "user", "model" (a feature value) or "dimension"
constexpr int kKeyRole = Qt::UserRole + 1;     // user: its name; model: the feature id
constexpr int kInputRole = Qt::UserRole + 2;   // model: input id
constexpr int kPathRole = Qt::UserRole + 3;    // "width" or "Extrude1.distance"
constexpr int kNameRole = Qt::UserRole + 4;    // the parameter's name (d5, width)
constexpr int kFavRole = Qt::UserRole + 5;     // starred

QString qs(const std::string& s) { return QString::fromStdString(s); }

QString number(double v) {
  QString t = QString::number(v, 'f', 6);
  while (t.contains(QLatin1Char('.')) && (t.endsWith(QLatin1Char('0')) || t.endsWith(QLatin1Char('.')))) t.chop(1);
  return t == QLatin1String("-0") ? QStringLiteral("0") : t;
}

QString withUnit(double internal, Unit u) {
  const QString n = number(fromInternal(internal, u));
  return u == Unit::None ? n : n + QLatin1Char(' ') + QString::fromUtf8(unitSymbol(u).data());
}
} // namespace

ParametersDialog::ParametersDialog(doc::Session& session, QWidget* parent) : QDialog(parent), session_(session) {
  setWindowTitle(tr("Parameters"));
  setObjectName(QStringLiteral("parametersDialog"));
  setWindowFlag(Qt::Tool);
  setAttribute(Qt::WA_DeleteOnClose);
  resize(720, 420);

  tree_ = new QTreeWidget;
  tree_->setObjectName(QStringLiteral("parameterTable"));
  tree_->setColumnCount(7);
  tree_->setHeaderLabels(
      {QString::fromUtf8("\u2605"), tr("Parameter"), tr("Name"), tr("Unit"), tr("Expression"), tr("Value"), tr("Comments")});
  tree_->setTreePosition(kParameter);   // the star column stays a narrow column of its own
  tree_->headerItem()->setToolTip(kStar, tr("Favorites: click a star to keep the parameter at the top"));
  tree_->setEditTriggers(QAbstractItemView::NoEditTriggers);
  tree_->setAlternatingRowColors(true);
  tree_->header()->setStretchLastSection(true);
  connect(tree_, &QTreeWidget::itemChanged, this, &ParametersDialog::onItemChanged);
  // Editable: any parameter's name, a user or feature value's expression,
  // a user parameter's comment.
  connect(tree_, &QTreeWidget::itemDoubleClicked, this, [this](QTreeWidgetItem* item, int column) {
    const QString kind = item->data(kName, kKindRole).toString();
    if (kind.isEmpty()) return;
    if (column == kName || (kind == QLatin1String("user") && (column == kExpression || column == kComment)) ||
        (kind == QLatin1String("model") && column == kExpression))
      tree_->editItem(item, column);
  });
  // A click on the star stars (or unstars) the parameter.
  connect(tree_, &QTreeWidget::itemClicked, this, [this](QTreeWidgetItem* item, int column) {
    const QString name = item->data(kName, kNameRole).toString();
    if (column != kStar || name.isEmpty()) return;
    showError(qs(session_.setParameterFavorite(name.toStdString(), !item->data(kName, kFavRole).toBool())));
  });

  filter_ = new QLineEdit;
  filter_->setObjectName(QStringLiteral("parameterFilter"));
  filter_->setPlaceholderText(tr("Filter"));
  filter_->setClearButtonEnabled(true);
  filter_->setToolTip(tr("Show only parameters whose name, expression, comment or feature contains this"));
  connect(filter_, &QLineEdit::textChanged, this, [this] { applyFilter(); });

  auto* add = new QPushButton(icon(QStringLiteral("parameters")), tr("Add"));
  add->setObjectName(QStringLiteral("addParameter"));
  add->setToolTip(tr("Add a user parameter"));
  connect(add, &QPushButton::clicked, this, &ParametersDialog::showAddForm);
  auto* del = new QPushButton(tr("Delete"));
  del->setObjectName(QStringLiteral("deleteParameter"));
  del->setToolTip(tr("Delete the selected user parameter (only if nothing uses it)"));
  connect(del, &QPushButton::clicked, this, &ParametersDialog::deleteSelected);
  auto* close = new QDialogButtonBox(QDialogButtonBox::Close);
  connect(close, &QDialogButtonBox::rejected, this, &QDialog::close);

  error_ = new QLabel;
  error_->setObjectName(QStringLiteral("error"));
  error_->setWordWrap(true);
  error_->setStyleSheet(QStringLiteral("color: palette(highlight);"));
  error_->hide();

  auto* hint = new QLabel(tr("Double-click an expression to change it, e.g. <i>width / 2 + 3 mm</i>, or a name "
                             "to rename it. "
                             "Expressions may use + - * / ^, parentheses, other parameters, pi and functions such as "
                             "sqrt, sin, cos, tan, atan, abs, min, max, round."));
  hint->setWordWrap(true);

  auto* buttons = new QHBoxLayout;
  buttons->addWidget(add);
  buttons->addWidget(del);
  buttons->addStretch();
  buttons->addWidget(close);
  auto* layout = new QVBoxLayout(this);
  layout->addWidget(hint);
  layout->addWidget(filter_);
  layout->addWidget(tree_, 1);
  layout->addWidget(error_);
  layout->addLayout(buttons);

  listener_ = session_.addListener([this] { scheduleRebuild(); });
  rebuild();
}

ParametersDialog::~ParametersDialog() { session_.removeListener(listener_); }

void ParametersDialog::scheduleRebuild() {
  // Never rebuild from inside the item signal that caused the change.
  if (rebuildPending_) return;
  rebuildPending_ = true;
  QTimer::singleShot(0, this, [this] {
    rebuildPending_ = false;
    rebuild();
  });
}

void ParametersDialog::rebuild() {
  building_ = true;
  const QSignalBlocker block(tree_);
  tree_->clear();
  auto& doc = session_.document();
  const Unit length = parseUnit(doc.lengthUnit()).value_or(Unit::Millimeter);
  const auto editable = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
  const auto favs = doc.favoriteParameters();
  auto isFav = [&](const std::string& n) { return std::find(favs.begin(), favs.end(), n) != favs.end(); };
  auto star = [&](QTreeWidgetItem* row, const std::string& name) {
    const bool fav = isFav(name);
    row->setText(kStar, fav ? QString::fromUtf8("\u2605") : QString::fromUtf8("\u2606"));
    if (fav) row->setForeground(kStar, QBrush(QColor(240, 180, 40)));
    row->setTextAlignment(kStar, Qt::AlignCenter);
    row->setToolTip(kStar, fav ? tr("Remove from Favorites") : tr("Add to Favorites"));
    row->setData(kName, kNameRole, qs(name));
    row->setData(kName, kFavRole, fav);
  };
  // One row per parameter; favourites appear again under Favorites.
  struct Row {
    QString kind, parameter, name, unit, expression, value, comment, path, input, tip;
    QVariant key;
  };
  std::vector<Row> userRows, favRows;
  std::vector<std::pair<std::string, std::vector<Row>>> modelRows;   // per feature, in timeline order

  for (const auto& p : doc.userParameters()) {
    const Unit u = parseUnit(p.unit).value_or(Unit::None);
    Row r{QStringLiteral("user"), QString(), qs(p.name), qs(p.unit), qs(p.expression), withUnit(p.value, u),
          qs(p.comment), qs(p.name), QString(), QString(), qs(p.name)};
    userRows.push_back(r);
  }
  const auto models = doc.modelParameters();
  for (const auto& f : doc.features()) {
    std::vector<Row> rows;
    for (const auto& m : models) {
      if (m.owner != f.name) continue;
      const Unit shown = dimensionOf(m.unit) == Dimension::Length ? length : m.unit;
      const QString value = m.unit == Unit::None ? number(m.value) : withUnit(m.value, shown);
      const QString unit = m.unit == Unit::None ? QString() : qs(std::string(unitSymbol(shown)));
      const QString expr = m.expression.empty() ? value : qs(m.expression);
      if (m.input.empty())
        rows.push_back({QStringLiteral("dimension"), tr("Dimension"), qs(m.name), unit, expr, value, QString(), qs(m.name),
                        QString(), tr("Sketch dimension: change its value in the sketch; rename it here."), QVariant()});
      else
        rows.push_back({QStringLiteral("model"), qs(m.label), qs(m.name), unit, expr, value, QString(),
                        qs(f.name + "." + m.input), qs(m.input), QString(), f.id});
    }
    if (!rows.empty()) modelRows.emplace_back(f.name, std::move(rows));
  }
  for (const auto& r : userRows)
    if (isFav(r.name.toStdString())) favRows.push_back(r);
  for (const auto& [owner, rows] : modelRows)
    for (const auto& r : rows)
      if (isFav(r.name.toStdString())) favRows.push_back(r);

  auto add = [&](QTreeWidgetItem* parent, const Row& r, bool primary) {
    auto* row = new QTreeWidgetItem(parent, {QString(), r.parameter, r.name, r.unit, r.expression, r.value, r.comment});
    row->setFlags(editable);
    row->setData(kName, kKindRole, r.kind);
    row->setData(kName, kKeyRole, r.key);
    row->setData(kName, kInputRole, r.input);
    // Tests find the main row by its path; the Favorites copy has its own.
    row->setData(kName, kPathRole, primary ? r.path : QStringLiteral("favorite:") + r.name);
    if (!r.tip.isEmpty()) row->setToolTip(kName, r.tip);
    star(row, r.name.toStdString());
  };
  if (!favRows.empty()) {
    auto* fav = new QTreeWidgetItem(tree_, {QString(), tr("Favorites")});
    for (const auto& r : favRows) add(fav, r, false);
  }
  auto* user = new QTreeWidgetItem(tree_, {QString(), tr("User Parameters")});
  user->setIcon(kParameter, icon(QStringLiteral("parameters")));
  for (const auto& r : userRows) add(user, r, true);
  auto* model = new QTreeWidgetItem(tree_, {QString(), tr("Model Parameters")});
  for (const auto& [owner, rows] : modelRows) {
    auto* group = new QTreeWidgetItem(model, {QString(), qs(owner)});
    for (const auto& f : doc.features())
      if (f.name == owner && !f.error.empty()) group->setToolTip(kParameter, qs(f.error));
    for (const auto& r : rows) add(group, r, true);
  }
  tree_->expandAll();
  for (int c = 0; c < kComment; ++c) tree_->resizeColumnToContents(c);
  building_ = false;
  applyFilter();
}

void ParametersDialog::applyFilter() {
  const QString text = filter_ ? filter_->text().trimmed() : QString();
  // A row shows when it matches; a group when anything in it shows (or its
  // own name, a feature's, matches: then all of it shows).
  std::function<bool(QTreeWidgetItem*, bool)> walk = [&](QTreeWidgetItem* it, bool parentMatch) -> bool {
    bool own = text.isEmpty() || parentMatch;
    if (!own)
      for (int c : {kParameter, kName, kExpression, kComment})
        own = own || it->text(c).contains(text, Qt::CaseInsensitive);
    if (it->childCount() == 0) {
      it->setHidden(!own);
      return own;
    }
    const bool groupMatch = own && it->parent();   // a feature's name: all its values
    bool any = false;
    for (int i = 0; i < it->childCount(); ++i) any = walk(it->child(i), groupMatch) || any;
    it->setHidden(!any);
    return any;
  };
  for (int i = 0; i < tree_->topLevelItemCount(); ++i) walk(tree_->topLevelItem(i), false);
}

void ParametersDialog::setFilterForTest(const QString& text) { filter_->setText(text); }

QMap<QString, QPair<QPoint, QPoint>> ParametersDialog::rowPoints() const {
  QMap<QString, QPair<QPoint, QPoint>> out;
  for (QTreeWidgetItemIterator it(tree_); *it; ++it) {
    const QString name = (*it)->data(kName, kNameRole).toString();
    if (name.isEmpty() || (*it)->data(kName, kPathRole).toString().startsWith(QLatin1String("favorite:"))) continue;
    const QRect star = tree_->visualItemRect(*it);
    if (star.isEmpty()) continue;   // hidden by the filter or scrolled away
    const int sx = tree_->header()->sectionViewportPosition(kStar) + tree_->header()->sectionSize(kStar) / 2;
    const int nx = tree_->header()->sectionViewportPosition(kName) + 12;
    out[name] = {tree_->viewport()->mapToGlobal(QPoint(sx, star.center().y())),
                 tree_->viewport()->mapToGlobal(QPoint(nx, star.center().y()))};
  }
  return out;
}

int ParametersDialog::visibleParameterRows() const {
  int n = 0;
  for (QTreeWidgetItemIterator it(tree_); *it; ++it) {
    bool shown = !(*it)->isHidden();
    for (QTreeWidgetItem* p = (*it)->parent(); p && shown; p = p->parent()) shown = !p->isHidden();
    if (shown && !(*it)->data(kName, kKindRole).toString().isEmpty()) ++n;
  }
  return n;
}

void ParametersDialog::onItemChanged(QTreeWidgetItem* item, int column) {
  if (building_) return;
  const QString kind = item->data(kName, kKindRole).toString();
  std::string err;
  if (column == kName) {
    const QString was = item->data(kName, kNameRole).toString();
    const QString now = item->text(kName).trimmed();
    if (was.isEmpty() || now == was) return;
    showError(qs(session_.renameParameter(was.toStdString(), now.toStdString())));
    scheduleRebuild();
    return;
  }
  if (kind == QLatin1String("user")) {
    if (column != kExpression && column != kComment) return;
    err = session_.setParameter(item->data(kName, kNameRole).toString().toStdString(),
                                item->text(kExpression).trimmed().toStdString(),
                                item->text(kComment).toStdString());
  } else if (kind == QLatin1String("model")) {
    if (column != kExpression) return;
    err = session_.editFeature(item->data(kName, kKeyRole).toInt(),
                               {{item->data(kName, kInputRole).toString().toStdString(),
                                 item->text(kExpression).trimmed().toStdString()}});
  } else {
    return;
  }
  showError(qs(err));
  scheduleRebuild();   // shows the new values, or puts the old text back
}

QTreeWidgetItem* ParametersDialog::findRow(const QString& parameter) const {
  for (QTreeWidgetItemIterator it(tree_); *it; ++it)
    if ((*it)->data(kName, kPathRole).toString() == parameter) return *it;
  return nullptr;
}

bool ParametersDialog::setExpressionForTest(const QString& parameter, const QString& expression) {
  if (rebuildPending_) {
    rebuildPending_ = false;
    rebuild();
  }
  QTreeWidgetItem* row = findRow(parameter);
  if (!row) return false;
  row->setText(kExpression, expression);   // emits itemChanged like an edit
  return true;
}

QString ParametersDialog::errorText() const { return error_->text(); }

void ParametersDialog::showError(const QString& text) {
  error_->setText(text);
  error_->setVisible(!text.isEmpty());
}

QString ParametersDialog::addParameter(const QString& name, const QString& unit, const QString& expression,
                                       const QString& comment) {
  const std::string err = session_.run(doc::kCmdAddUserParameter, {{"name", name.trimmed().toStdString()},
                                                                   {"unit", unit.toStdString()},
                                                                   {"expression", expression.trimmed().toStdString()},
                                                                   {"comment", comment.toStdString()}});
  return qs(err);
}

void ParametersDialog::showAddForm() {
  QDialog form(this);
  form.setWindowTitle(tr("Add User Parameter"));
  auto* name = new QLineEdit;
  name->setObjectName(QStringLiteral("name"));
  auto* unit = new QComboBox;
  for (const char* u : {"mm", "cm", "m", "in", "ft", "deg", "rad"}) unit->addItem(QString::fromLatin1(u), QString::fromLatin1(u));
  unit->addItem(tr("No units"), QString());
  unit->setCurrentIndex(unit->findData(qs(session_.document().lengthUnit())));
  auto* expression = new QLineEdit(QStringLiteral("1"));
  auto* comment = new QLineEdit;
  auto* err = new QLabel;
  err->setWordWrap(true);
  err->setStyleSheet(QStringLiteral("color: palette(highlight);"));
  auto* box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  auto* lay = new QFormLayout(&form);
  lay->addRow(tr("Name"), name);
  lay->addRow(tr("Unit"), unit);
  lay->addRow(tr("Expression"), expression);
  lay->addRow(tr("Comment"), comment);
  lay->addRow(err);
  lay->addRow(box);
  connect(box, &QDialogButtonBox::rejected, &form, &QDialog::reject);
  connect(box, &QDialogButtonBox::accepted, &form, [&] {
    const QString e = addParameter(name->text(), unit->currentData().toString(), expression->text(), comment->text());
    if (e.isEmpty()) form.accept();
    else err->setText(e);
  });
  form.exec();
}

void ParametersDialog::deleteSelected() {
  QTreeWidgetItem* item = tree_->currentItem();
  if (!item || item->data(kName, kKindRole).toString() != QLatin1String("user")) {
    showError(tr("Select a user parameter to delete."));
    return;
  }
  showError(qs(session_.deleteParameter(item->data(kName, kNameRole).toString().toStdString())));
}

} // namespace tsr::app
