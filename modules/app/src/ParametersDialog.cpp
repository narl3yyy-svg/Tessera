#include "ParametersDialog.h"
#include "Icons.h"

#include "tsr/doc/DocCommands.h"

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

namespace tsr::app {

namespace {
enum Column { kParameter = 0, kUnit, kExpression, kValue, kComment };
constexpr int kKindRole = Qt::UserRole;        // "user" or "model"
constexpr int kKeyRole = Qt::UserRole + 1;     // parameter name or feature id
constexpr int kInputRole = Qt::UserRole + 2;   // model: input id
constexpr int kPathRole = Qt::UserRole + 3;    // "width" or "Extrude1.distance"

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
  tree_->setColumnCount(5);
  tree_->setHeaderLabels({tr("Parameter"), tr("Unit"), tr("Expression"), tr("Value"), tr("Comments")});
  tree_->setEditTriggers(QAbstractItemView::NoEditTriggers);
  tree_->setAlternatingRowColors(true);
  tree_->header()->setStretchLastSection(true);
  connect(tree_, &QTreeWidget::itemChanged, this, &ParametersDialog::onItemChanged);
  // Only the expression (and a user parameter's comment) can be edited.
  connect(tree_, &QTreeWidget::itemDoubleClicked, this, [this](QTreeWidgetItem* item, int column) {
    const QString kind = item->data(kParameter, kKindRole).toString();
    if ((kind == QLatin1String("user") && (column == kExpression || column == kComment)) ||
        (kind == QLatin1String("model") && column == kExpression))
      tree_->editItem(item, column);
  });

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

  auto* hint = new QLabel(tr("Double-click an expression to change it, e.g. <i>width / 2 + 3 mm</i>. "
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

  auto* user = new QTreeWidgetItem(tree_, {tr("User Parameters")});
  user->setIcon(kParameter, icon(QStringLiteral("parameters")));
  for (const auto& p : doc.userParameters()) {
    const Unit u = parseUnit(p.unit).value_or(Unit::None);
    auto* row = new QTreeWidgetItem(user, {qs(p.name), qs(p.unit), qs(p.expression), withUnit(p.value, u), qs(p.comment)});
    row->setFlags(editable);
    row->setData(kParameter, kKindRole, QStringLiteral("user"));
    row->setData(kParameter, kKeyRole, qs(p.name));
    row->setData(kParameter, kPathRole, qs(p.name));
  }

  auto* model = new QTreeWidgetItem(tree_, {tr("Model Parameters")});
  for (const auto& f : doc.features()) {
    const Command* cmd = session_.commands().find(f.commandId);
    if (!cmd) continue;
    QTreeWidgetItem* group = nullptr;
    for (const InputDef& in : cmd->def().inputs) {
      if (in.type != InputType::Real && in.type != InputType::Integer) continue;
      if (!isInputVisible(in, f.inputs)) continue;
      auto it = f.inputs.find(in.id);
      if (it == f.inputs.end()) continue;
      QString value;
      if (auto d = std::get_if<double>(&it->second)) {
        const Unit shown = dimensionOf(in.unit) == Dimension::Length ? length : in.unit;
        value = withUnit(*d, shown);
      } else if (auto i = std::get_if<std::int64_t>(&it->second)) {
        value = QString::number(*i);
      } else {
        continue;
      }
      if (!group) {
        group = new QTreeWidgetItem(model, {qs(f.name)});
        if (!f.error.empty()) group->setToolTip(kParameter, qs(f.error));
      }
      const std::string expr = inputExpression(f.inputs, in.id);
      const QString unit = in.type == InputType::Integer ? QString()
                           : qs(std::string(unitSymbol(dimensionOf(in.unit) == Dimension::Length ? length : in.unit)));
      auto* row = new QTreeWidgetItem(group, {qs(in.label), unit, expr.empty() ? value : qs(expr), value, QString()});
      row->setFlags(editable);
      row->setData(kParameter, kKindRole, QStringLiteral("model"));
      row->setData(kParameter, kKeyRole, f.id);
      row->setData(kParameter, kInputRole, qs(in.id));
      row->setData(kParameter, kPathRole, qs(f.name + "." + in.id));
    }
    // A sketch's named dimensions (d1, d2 ...): usable in any expression.
    // Changed in the sketch (double-click the dimension).
    for (const auto& m : doc.modelParameters()) {
      if (m.owner != f.name) continue;
      if (!group) group = new QTreeWidgetItem(model, {qs(f.name)});
      const Unit u = m.angle ? Unit::Degree : length;
      const QString value = withUnit(m.value, u);
      auto* row = new QTreeWidgetItem(group, {qs(m.name), qs(std::string(unitSymbol(u))),
                                              m.expression.empty() ? value : qs(m.expression), value, QString()});
      row->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      row->setToolTip(kParameter, tr("Sketch dimension; edit it in the sketch."));
      row->setData(kParameter, kKindRole, QStringLiteral("dimension"));
      row->setData(kParameter, kPathRole, qs(m.name));
    }
  }
  tree_->expandAll();
  for (int c = 0; c < kComment; ++c) tree_->resizeColumnToContents(c);
  building_ = false;
}

void ParametersDialog::onItemChanged(QTreeWidgetItem* item, int column) {
  if (building_) return;
  const QString kind = item->data(kParameter, kKindRole).toString();
  std::string err;
  if (kind == QLatin1String("user")) {
    if (column != kExpression && column != kComment) return;
    err = session_.setParameter(item->data(kParameter, kKeyRole).toString().toStdString(),
                                item->text(kExpression).trimmed().toStdString(),
                                item->text(kComment).toStdString());
  } else if (kind == QLatin1String("model")) {
    if (column != kExpression) return;
    err = session_.editFeature(item->data(kParameter, kKeyRole).toInt(),
                               {{item->data(kParameter, kInputRole).toString().toStdString(),
                                 item->text(kExpression).trimmed().toStdString()}});
  } else {
    return;
  }
  showError(qs(err));
  scheduleRebuild();   // shows the new values, or puts the old text back
}

QTreeWidgetItem* ParametersDialog::findRow(const QString& parameter) const {
  for (QTreeWidgetItemIterator it(tree_); *it; ++it)
    if ((*it)->data(kParameter, kPathRole).toString() == parameter) return *it;
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
  if (!item || item->data(kParameter, kKindRole).toString() != QLatin1String("user")) {
    showError(tr("Select a user parameter to delete."));
    return;
  }
  showError(qs(session_.deleteParameter(item->data(kParameter, kKeyRole).toString().toStdString())));
}

} // namespace tsr::app
