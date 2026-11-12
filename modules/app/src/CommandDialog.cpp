#include "CommandDialog.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

#include <cmath>
#include <limits>

namespace tsr::app {

CommandDialog::CommandDialog(doc::Session& session, std::unique_ptr<CommandSession> cmd, QWidget* parent)
    : QDialog(parent), session_(session), cmd_(std::move(cmd)) {
  const CommandDef& def = cmd_->def();
  setWindowTitle(QString::fromStdString(def.name));
  setObjectName(QString::fromStdString(def.id));
  setMinimumWidth(300);
  const Unit lengthUnit = parseUnit(session_.document().lengthUnit()).value_or(Unit::Millimeter);

  auto* form = new QFormLayout;
  form_ = form;
  form->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  form->setHorizontalSpacing(14);
  for (const InputDef& in : def.inputs) {
    const QString label = QString::fromStdString(in.label);
    const QString tip = QString::fromStdString(in.tooltip);
    const Value& cur = cmd_->inputs().at(in.id);
    QWidget* w = nullptr;
    const std::string id = in.id;

    switch (in.type) {
      case InputType::Real: {
        auto* sb = new QDoubleSpinBox;
        // Lengths are shown in the document's unit (Document Settings).
        const Unit shown = dimensionOf(in.unit) == Dimension::Length ? lengthUnit : in.unit;
        sb->setDecimals(shown == Unit::Inch ? 4 : 3);
        const double step = shown == Unit::Inch ? 0.0625 : shown == Unit::Degree ? 1.0 : fromInternal(0.1, shown);
        sb->setSingleStep(step > 0 ? step : 1.0);
        double lo = in.min ? fromInternal(*in.min, shown) : -1e9;
        if (in.min && in.minExclusive) lo += std::pow(10.0, -sb->decimals());
        sb->setRange(lo, in.max ? fromInternal(*in.max, shown) : 1e9);
        if (shown != Unit::None) sb->setSuffix(QStringLiteral(" ") + QString::fromUtf8(unitSymbol(shown).data()));
        if (auto p = std::get_if<double>(&cur)) sb->setValue(fromInternal(*p, shown));
        sb->setAccelerated(true);
        const Unit unit = shown;
        connect(sb, &QDoubleSpinBox::valueChanged, this,
                [this, id, unit](double v) { onInputChanged(id, toInternal(v, unit)); });
        w = sb;
        break;
      }
      case InputType::Integer: {
        auto* sb = new QSpinBox;
        sb->setRange(in.min ? static_cast<int>(*in.min) : std::numeric_limits<int>::min(),
                     in.max ? static_cast<int>(*in.max) : std::numeric_limits<int>::max());
        if (auto p = std::get_if<std::int64_t>(&cur)) sb->setValue(static_cast<int>(*p));
        connect(sb, &QSpinBox::valueChanged, this,
                [this, id](int v) { onInputChanged(id, static_cast<std::int64_t>(v)); });
        w = sb;
        break;
      }
      case InputType::Bool: {
        auto* cb = new QCheckBox;
        if (auto p = std::get_if<bool>(&cur)) cb->setChecked(*p);
        connect(cb, &QCheckBox::toggled, this, [this, id](bool v) { onInputChanged(id, v); });
        w = cb;
        break;
      }
      case InputType::String: {
        auto* le = new QLineEdit;
        if (auto p = std::get_if<std::string>(&cur)) le->setText(QString::fromStdString(*p));
        connect(le, &QLineEdit::textEdited, this,
                [this, id](const QString& t) { onInputChanged(id, t.toStdString()); });
        w = le;
        break;
      }
      case InputType::Choice: {
        auto* combo = new QComboBox;
        for (const auto& c : in.choices) combo->addItem(QString::fromStdString(c));
        if (auto p = std::get_if<std::string>(&cur)) combo->setCurrentText(QString::fromStdString(*p));
        connect(combo, &QComboBox::currentTextChanged, this,
                [this, id](const QString& t) { onInputChanged(id, t.toStdString()); });
        w = combo;
        break;
      }
      case InputType::Sketch: {
        auto* combo = new QComboBox;
        if (in.optional) combo->addItem(tr("(most recent sketch)"), QString());
        for (const auto& s : session_.document().sketches())
          combo->addItem(QString::fromStdString(s.name), QString::fromStdString(s.name));
        if (auto p = std::get_if<std::string>(&cur); p && !p->empty()) {
          const QString name = QString::fromStdString(*p);
          if (combo->findData(name) < 0) combo->addItem(name, name);
          combo->setCurrentIndex(combo->findData(name));
        }
        connect(combo, &QComboBox::currentIndexChanged, this, [this, id, combo](int) {
          onInputChanged(id, combo->currentData().toString().toStdString());
        });
        sketchInput_ = combo;
        w = combo;
        break;
      }
      case InputType::Edges:
      case InputType::Faces:
      case InputType::Bodies: {
        // Filled by clicking in the 3D view.
        auto* box = new QWidget;
        auto* row = new QHBoxLayout(box);
        row->setContentsMargins(0, 0, 0, 0);
        auto* label = new QLabel;
        auto* clear = new QPushButton(tr("Clear"));
        row->addWidget(label, 1);
        row->addWidget(clear);
        if (in.type == InputType::Edges) {
          edgesLabel_ = label;
          edgesId_ = id;
          clear->setObjectName(QStringLiteral("clearEdges"));
        } else if (in.type == InputType::Faces) {
          facesLabel_ = label;
          facesId_ = id;
          clear->setObjectName(QStringLiteral("clearFaces"));
        } else {
          bodiesLabel_ = label;
          bodiesId_ = id;
          clear->setObjectName(QStringLiteral("clearBodies"));
        }
        connect(clear, &QPushButton::clicked, this, [this, id] {
          onInputChanged(id, std::string());
          updateProfilesLabel();
        });
        w = box;
        break;
      }
      case InputType::Profiles: {
        // Filled by clicking profiles in the 3D view.
        auto* box = new QWidget;
        auto* row = new QHBoxLayout(box);
        row->setContentsMargins(0, 0, 0, 0);
        profilesLabel_ = new QLabel;
        auto* clear = new QPushButton(tr("Clear"));
        clear->setObjectName(QStringLiteral("clearProfiles"));
        row->addWidget(profilesLabel_, 1);
        row->addWidget(clear);
        profilesId_ = id;
        connect(clear, &QPushButton::clicked, this, [this] { setProfiles(currentSketch(), QString()); });
        w = box;
        break;
      }
      case InputType::Body: {
        // Picked from a list or by clicking the body in the 3D view.
        auto* combo = new QComboBox;
        if (in.optional) combo->addItem(tr("(most recent body)"), QString());
        for (const auto& b : session_.document().bodies())
          combo->addItem(QString::fromStdString(b.name), QString::fromStdString(b.name));
        if (auto p = std::get_if<std::string>(&cur); p && !p->empty()) {
          const QString name = QString::fromStdString(*p);
          if (combo->findData(name) < 0) combo->addItem(name, name);
          combo->setCurrentIndex(combo->findData(name));
        }
        connect(combo, &QComboBox::currentIndexChanged, this, [this, id, combo](int) {
          onInputChanged(id, combo->currentData().toString().toStdString());
        });
        if (!bodyInput_) bodyInput_ = combo;
        // A required body starts as the first one listed.
        if (!in.optional && combo->count() > 0 && std::get_if<std::string>(&cur) && std::get<std::string>(cur).empty())
          (void)cmd_->setInput(id, combo->currentData().toString().toStdString());
        w = combo;
        break;
      }
    }
    w->setObjectName(QString::fromStdString(in.id));
    w->setToolTip(tip);
    w->setAccessibleName(label);
    form->addRow(label, w);
    if (!in.visibleWhen.empty()) conditional_.emplace_back(w, in.visibleWhen);
  }
  updateVisibility();

  error_ = new QLabel;
  error_->setObjectName(QStringLiteral("error"));
  error_->setWordWrap(true);
  error_->setStyleSheet(QStringLiteral("color: palette(highlight);"));
  buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  connect(buttons_, &QDialogButtonBox::accepted, this, &CommandDialog::accept);
  connect(buttons_, &QDialogButtonBox::rejected, this, &CommandDialog::reject);

  auto* layout = new QVBoxLayout(this);
  layout->setContentsMargins(10, 6, 10, 8);
  auto* title = new QLabel(QStringLiteral("—  ") + QString::fromStdString(def.name).toUpper());
  title->setObjectName(QStringLiteral("panelTitle"));
  layout->addWidget(title);
  layout->addLayout(form);
  form->setContentsMargins(0, 4, 0, 4);
  layout->addWidget(error_);
  layout->addWidget(buttons_);

  refreshPreview();
}

CommandDialog::~CommandDialog() {
  if (cmd_ && !cmd_->finished()) {
    cmd_->cancel();
    session_.notifyChanged();
  }
}

void CommandDialog::onInputChanged(const std::string& id, const Value& v) {
  if (auto err = cmd_->setInput(id, v); !err.empty()) {
    showError(err);
    return;
  }
  refreshPreview();
}

void CommandDialog::adjustAfterResize() {
  // Embedded panels keep their right edge when rows appear or disappear.
  if (QWidget* p = parentWidget(); p && !isWindow()) move(p->width() - width() - 12, y());
}

void CommandDialog::updateVisibility() {
  for (const auto& [w, rule] : conditional_) {
    const auto eq = rule.find('=');
    if (eq == std::string::npos) continue;
    const std::string id = rule.substr(0, eq);
    std::string value;
    if (auto it = cmd_->inputs().find(id); it != cmd_->inputs().end())
      if (auto s = std::get_if<std::string>(&it->second)) value = *s;
    bool show = false;
    size_t start = eq + 1;
    while (start <= rule.size()) {
      size_t end = rule.find('|', start);
      if (end == std::string::npos) end = rule.size();
      show = show || rule.substr(start, end - start) == value;
      start = end + 1;
    }
    form_->setRowVisible(w, show);
  }
  adjustSize();
  adjustAfterResize();
}

void CommandDialog::refreshPreview() {
  updateVisibility();
  updateProfilesLabel();
  emit inputsChanged();
  showError(cmd_->preview());
  session_.notifyChanged();
}

void CommandDialog::showError(const std::string& err) {
  error_->setText(QString::fromStdString(err));
  error_->setVisible(!err.empty());
  buttons_->button(QDialogButtonBox::Ok)->setEnabled(err.empty());
}

void CommandDialog::accept() {
  const std::string err = cmd_->execute();
  session_.notifyChanged();
  if (!err.empty()) {
    showError(err);
    return;
  }
  QDialog::accept();
}

void CommandDialog::reject() {
  cmd_->cancel();
  session_.notifyChanged();
  QDialog::reject();
}

bool CommandDialog::hasProfilesInput() const { return !profilesId_.empty(); }
bool CommandDialog::hasEdgesInput() const { return !edgesId_.empty(); }
bool CommandDialog::hasFacesInput() const { return !facesId_.empty(); }
bool CommandDialog::hasBodiesInput() const { return !bodiesId_.empty(); }

QString CommandDialog::stringInput(const std::string& id) const {
  if (id.empty()) return {};
  if (auto s = std::get_if<std::string>(&cmd_->inputs().at(id))) return QString::fromStdString(*s);
  return {};
}
QString CommandDialog::currentFaces() const { return stringInput(facesId_); }
QString CommandDialog::currentTools() const { return stringInput(bodiesId_); }

void CommandDialog::setFaces(const QString& faces) {
  if (!facesId_.empty()) onInputChanged(facesId_, faces.toStdString());
  updateProfilesLabel();
}

void CommandDialog::setTools(const QString& bodies) {
  if (!bodiesId_.empty()) onInputChanged(bodiesId_, bodies.toStdString());
  updateProfilesLabel();
}

QString CommandDialog::currentEdges() const {
  if (edgesId_.empty()) return {};
  if (auto s = std::get_if<std::string>(&cmd_->inputs().at(edgesId_))) return QString::fromStdString(*s);
  return {};
}

QString CommandDialog::currentBody() const {
  for (const auto& in : cmd_->def().inputs)
    if (in.type == InputType::Body)
      if (auto s = std::get_if<std::string>(&cmd_->inputs().at(in.id))) return QString::fromStdString(*s);
  return {};
}

void CommandDialog::setEdges(const QString& edges) {
  if (!edgesId_.empty()) onInputChanged(edgesId_, edges.toStdString());
  updateProfilesLabel();
}

QString CommandDialog::currentSketch() const {
  for (const auto& in : cmd_->def().inputs)
    if (in.type == InputType::Sketch)
      if (auto s = std::get_if<std::string>(&cmd_->inputs().at(in.id))) return QString::fromStdString(*s);
  return {};
}

QString CommandDialog::currentProfiles() const {
  if (profilesId_.empty()) return {};
  if (auto s = std::get_if<std::string>(&cmd_->inputs().at(profilesId_))) return QString::fromStdString(*s);
  return {};
}

void CommandDialog::setProfiles(const QString& sketch, const QString& profiles) {
  if (sketchInput_ && !sketch.isEmpty() && sketchInput_->currentData().toString() != sketch) {
    int i = sketchInput_->findData(sketch);
    if (i < 0) {
      sketchInput_->addItem(sketch, sketch);
      i = sketchInput_->count() - 1;
    }
    const QSignalBlocker block(sketchInput_);
    sketchInput_->setCurrentIndex(i);
    for (const auto& in : cmd_->def().inputs)
      if (in.type == InputType::Sketch) (void)cmd_->setInput(in.id, sketch.toStdString());
  }
  if (!profilesId_.empty()) onInputChanged(profilesId_, profiles.toStdString());
  updateProfilesLabel();
}

void CommandDialog::updateProfilesLabel() {
  auto count = [](const QString& s) { return s.isEmpty() ? 0 : static_cast<int>(s.count(QLatin1Char(';'))) + 1; };
  if (edgesLabel_) {
    const int n = count(currentEdges());
    edgesLabel_->setText(n == 0 ? tr("Click edges in the canvas") : tr("%n edge(s)", nullptr, n));
  }
  if (facesLabel_) {
    const int n = count(currentFaces());
    facesLabel_->setText(n == 0 ? tr("None (click faces to open)") : tr("%n face(s)", nullptr, n));
  }
  if (bodiesLabel_) {
    const QString t = currentTools();
    bodiesLabel_->setText(t.isEmpty() ? tr("Click bodies in the canvas") : t);
  }
  if (!profilesLabel_) return;
  const QString p = currentProfiles();
  const int n = p.isEmpty() ? 0 : p.count(QLatin1Char(';')) + 1;
  profilesLabel_->setText(n == 0 ? tr("All (click profiles to choose)") : tr("%n selected", nullptr, n));
}

bool CommandDialog::pickBody(const QString& name) {
  if (!bodyInput_ || !bodyInput_->isEnabled()) return false;
  int i = bodyInput_->findData(name);
  if (i < 0) return false;
  bodyInput_->setCurrentIndex(i);
  return true;
}

bool CommandDialog::setInputForTest(const QString& id, const QVariant& value) {
  QWidget* w = findChild<QWidget*>(id);
  if (auto* combo = qobject_cast<QComboBox*>(w)) {
    int i = combo->findText(value.toString());
    if (i < 0) i = combo->findData(value.toString());
    if (i < 0) return false;
    combo->setCurrentIndex(i);
    return true;
  }
  if (auto* sb = qobject_cast<QDoubleSpinBox*>(w)) { sb->setValue(value.toDouble()); return true; }
  if (auto* sb = qobject_cast<QSpinBox*>(w)) { sb->setValue(value.toInt()); return true; }
  if (auto* cb = qobject_cast<QCheckBox*>(w)) { cb->setChecked(value.toBool()); return true; }
  if (auto* le = qobject_cast<QLineEdit*>(w)) {
    le->setText(value.toString());
    emit le->textEdited(le->text()); // setText does not emit textEdited
    return true;
  }
  return false;
}

} // namespace tsr::app
