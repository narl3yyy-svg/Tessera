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

#include "tsr/core/Expression.h"

#include <cmath>
#include <functional>
#include <limits>
#include <optional>

namespace tsr::app {

namespace {

// "10 mm" with trailing zeros dropped.
QString formatNumber(double v, int decimals, Unit u) {
  QString t = QString::number(v, 'f', decimals);
  if (t.contains(QLatin1Char('.'))) {
    while (t.endsWith(QLatin1Char('0'))) t.chop(1);
    if (t.endsWith(QLatin1Char('.'))) t.chop(1);
  }
  if (t == QLatin1String("-0")) t = QStringLiteral("0");
  if (u != Unit::None) t += QStringLiteral(" ") + QString::fromUtf8(unitSymbol(u).data());
  return t;
}

} // namespace

// A spin box that also takes expressions ("width / 2 + 3 mm"). Arrows and the
// wheel step the number; typed text is evaluated against the document's
// parameters, and an expression stays visible once entered.
class ExpressionSpinBox final : public QDoubleSpinBox {
public:
  using Evaluate = std::function<std::optional<double>(const QString&)>;   // display units out
  ExpressionSpinBox(Unit shown, Evaluate eval) : shown_(shown), eval_(std::move(eval)) {
    setKeyboardTracking(false);
    setCorrectionMode(QAbstractSpinBox::CorrectToPreviousValue);
  }
  const QString& expression() const { return expression_; }
  void setExpression(const QString& e) {
    expression_ = e;
    lineEdit()->setText(textFromValue(value()));
  }
  QString typedText() const { return lineEdit()->text().trimmed(); }
  std::optional<double> evaluate(const QString& t) const { return eval_(t); }
  // Types text and finishes the edit, as a user pressing Enter would.
  void typeText(const QString& t) {
    lineEdit()->setText(t);
    emit editingFinished();
  }

protected:
  QValidator::State validate(QString& text, int&) const override {
    return eval_(text) ? QValidator::Acceptable : QValidator::Intermediate;
  }
  double valueFromText(const QString& text) const override { return eval_(text).value_or(value()); }
  QString textFromValue(double v) const override {
    return expression_.isEmpty() ? formatNumber(v, decimals(), shown_) : expression_;
  }
  void fixup(QString&) const override {}
  void stepBy(int steps) override {
    expression_.clear();
    QDoubleSpinBox::stepBy(steps);
  }

private:
  Unit shown_;
  Evaluate eval_;
  QString expression_;
};

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
        // Lengths are shown in the document's unit (Document Settings).
        const Unit shown = dimensionOf(in.unit) == Dimension::Length ? lengthUnit : in.unit;
        const Unit evalUnit = in.unit;
        auto* sb = new ExpressionSpinBox(shown, [this, evalUnit, shown](const QString& t) -> std::optional<double> {
          try {
            return fromInternal(session_.document().evaluate(t.toStdString(), evalUnit), shown);
          } catch (const std::exception&) {
            return std::nullopt;
          }
        });
        sb->setDecimals(shown == Unit::Inch ? 4 : 3);
        const double step = shown == Unit::Inch ? 0.0625 : shown == Unit::Degree ? 1.0 : fromInternal(0.1, shown);
        sb->setSingleStep(step > 0 ? step : 1.0);
        // Out-of-range values are reported by the command (expressions can
        // produce any value), so the box itself does not clamp.
        sb->setRange(-1e9, 1e9);
        if (auto p = std::get_if<double>(&cur)) sb->setValue(fromInternal(*p, shown));
        if (const std::string e = inputExpression(cmd_->inputs(), id); !e.empty())
          sb->setExpression(QString::fromStdString(e));
        sb->setAccelerated(true);
        // Sends the typed expression, or the number after stepping / typing a
        // plain value. Both signals can fire for one edit; send it once.
        auto commit = [this, id, sb, shown] {
          const QString t = sb->typedText();
          const std::optional<double> typed = sb->evaluate(t);
          const bool expression = typed && !isPlainQuantity(t.toStdString());
          const Value v = expression ? Value(t.toStdString()) : Value(toInternal(typed ? *typed : sb->value(), shown));
          if (lastSent_[id] == v) return;
          lastSent_[id] = v;
          if (expression) {
            sb->setExpression(t);
            const QSignalBlocker block(sb);
            sb->setValue(*typed);
          } else if (!sb->expression().isEmpty()) {
            sb->setExpression(QString());
          }
          onInputChanged(id, v);
        };
        connect(sb, &QDoubleSpinBox::valueChanged, this, commit);
        connect(sb, &QAbstractSpinBox::editingFinished, this, commit);
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
      case InputType::Plane: {
        auto* combo = new QComboBox;
        for (const char* o : {"XY", "XZ", "YZ"}) combo->addItem(QString::fromLatin1(o), QString::fromLatin1(o));
        for (const auto& pl : session_.document().planes())
          combo->addItem(QString::fromStdString(pl.name), QString::fromStdString(pl.name));
        if (auto p = std::get_if<std::string>(&cur); p && !p->empty()) {
          const QString name = QString::fromStdString(*p);
          if (combo->findData(name) < 0) combo->addItem(name.startsWith(QLatin1String("custom:")) ? tr("Picked face") : name, name);
          combo->setCurrentIndex(combo->findData(name));
        }
        connect(combo, &QComboBox::currentIndexChanged, this, [this, id, combo](int) {
          onInputChanged(id, combo->currentData().toString().toStdString());
        });
        if (!planeInput_) planeInput_ = combo;
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
      case InputType::Axis: {
        auto* combo = new QComboBox;
        for (const char* o : {"X", "Y", "Z"}) combo->addItem(QString::fromLatin1(o), QString::fromLatin1(o));
        for (const auto& a : session_.document().axes())
          combo->addItem(QString::fromStdString(a.name), QString::fromStdString(a.name));
        if (auto p = std::get_if<std::string>(&cur); p && !p->empty()) {
          const QString name = QString::fromStdString(*p);
          if (combo->findData(name) < 0) combo->addItem(name, name);
          combo->setCurrentIndex(combo->findData(name));
        }
        connect(combo, &QComboBox::currentIndexChanged, this, [this, id, combo](int) {
          onInputChanged(id, combo->currentData().toString().toStdString());
        });
        w = combo;
        break;
      }
      case InputType::JointOrigin: {
        auto* box = new QWidget;
        auto* row = new QHBoxLayout(box);
        row->setContentsMargins(0, 0, 0, 0);
        auto* label = new QLabel;
        auto* clear = new QPushButton(tr("Clear"));
        clear->setObjectName(QStringLiteral("clear_") + QString::fromStdString(id));
        row->addWidget(label, 1);
        row->addWidget(clear);
        jointIds_.emplace_back(id, label);
        connect(clear, &QPushButton::clicked, this, [this, id] {
          onInputChanged(id, std::string());
          updateProfilesLabel();
        });
        w = box;
        break;
      }
      case InputType::Edges:
      case InputType::Faces:
      case InputType::Vertices:
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
        } else if (in.type == InputType::Vertices) {
          verticesLabel_ = label;
          verticesId_ = id;
          clear->setObjectName(QStringLiteral("clearVertices"));
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
  buttons_->button(QDialogButtonBox::Ok)->setObjectName(QStringLiteral("panelOk"));
  buttons_->button(QDialogButtonBox::Cancel)->setObjectName(QStringLiteral("panelCancel"));
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
    InputDef d;
    d.visibleWhen = rule;
    form_->setRowVisible(w, isInputVisible(d, cmd_->inputs()));
  }
  adjustSize();
  adjustAfterResize();
}

void CommandDialog::setRequireSelection(bool on) {
  requireSelection_ = on;
  refreshPreview();
}

bool CommandDialog::waitingForSelection() const {
  return requireSelection_ && currentProfiles().isEmpty() && currentFaces().isEmpty();
}

void CommandDialog::refreshPreview() {
  updateVisibility();
  updateProfilesLabel();
  if (waitingForSelection()) {
    cmd_->clearPreview();
    emit inputsChanged();
    error_->setText(tr("Select sketch profiles or planar faces to extrude."));
    error_->setVisible(true);
    buttons_->button(QDialogButtonBox::Ok)->setEnabled(false);
    session_.notifyChanged();
    return;
  }
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
bool CommandDialog::hasPlaneInput() const { return planeInput_ != nullptr; }

bool CommandDialog::planeInputShown() const {
  if (!planeInput_) return false;
  const InputDef* d = cmd_->def().input(planeInput_->objectName().toStdString());
  return !d || isInputVisible(*d, cmd_->inputs());
}

void CommandDialog::pickPlane(const QString& spec, const QString& label) {
  if (!planeInput_) return;
  int i = planeInput_->findData(spec);
  if (i < 0) {
    planeInput_->addItem(spec.startsWith(QLatin1String("custom:")) ? tr("Picked %1").arg(label) : label, spec);
    i = planeInput_->count() - 1;
  }
  planeInput_->setCurrentIndex(i);
}
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

void CommandDialog::pickJointOrigin(const QString& spec) {
  if (jointIds_.empty()) return;
  std::string target = jointIds_.back().first;
  for (const auto& [id, label] : jointIds_)
    if (stringInput(id).isEmpty()) {
      target = id;
      break;
    }
  onInputChanged(target, spec.toStdString());
  updateProfilesLabel();
}

void CommandDialog::setVertices(const QString& v) {
  if (!verticesId_.empty()) onInputChanged(verticesId_, v.toStdString());
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
    facesLabel_->setText(n == 0 ? tr("None (click faces)") : tr("%n face(s)", nullptr, n));
  }
  for (const auto& [id, label] : jointIds_) {
    const QString spec = stringInput(id);
    const QStringList parts = spec.split(QLatin1Char('|'));
    label->setText(parts.size() < 2 ? tr("Click a face, edge or point") : tr("%1: %2").arg(parts[0], parts[1]));
  }
  if (verticesLabel_) {
    const int n = count(currentVertices());
    verticesLabel_->setText(n == 0 ? tr("Click vertices in the canvas") : tr("%n vertex(es)", nullptr, n));
  }
  if (bodiesLabel_) {
    const QString t = currentTools();
    bodiesLabel_->setText(t.isEmpty() ? tr("Click bodies in the canvas") : t);
  }
  if (!profilesLabel_) return;
  const QString p = currentProfiles();
  const int n = p.isEmpty() ? 0 : p.count(QLatin1Char(';')) + 1;
  profilesLabel_->setText(n > 0              ? tr("%n selected", nullptr, n)
                          : requireSelection_ ? tr("None (click profiles)")
                                              : tr("All (click profiles to choose)"));
}

bool CommandDialog::pickBody(const QString& name) {
  if (!bodyInput_ || !bodyInput_->isEnabled()) return false;
  int i = bodyInput_->findData(name);
  if (i < 0) return false;
  bodyInput_->setCurrentIndex(i);
  return true;
}

std::optional<double> CommandDialog::realInput(const QString& id) const {
  auto it = cmd_->inputs().find(id.toStdString());
  if (it == cmd_->inputs().end()) return std::nullopt;
  if (auto d = std::get_if<double>(&it->second)) return *d;
  return std::nullopt;
}

QString CommandDialog::displayText(const QString& id) const {
  if (const std::string e = inputExpression(cmd_->inputs(), id.toStdString()); !e.empty()) return QString::fromStdString(e);
  const InputDef* d = cmd_->def().input(id.toStdString());
  const auto v = realInput(id);
  if (!d || !v) return {};
  const Unit length = parseUnit(session_.document().lengthUnit()).value_or(Unit::Millimeter);
  const Unit shown = dimensionOf(d->unit) == Dimension::Length ? length : d->unit;
  return formatNumber(fromInternal(*v, shown), shown == Unit::Inch ? 4 : 2, shown);
}

void CommandDialog::setRealInput(const QString& id, double value) {
  if (auto* sb = dynamic_cast<ExpressionSpinBox*>(findChild<QDoubleSpinBox*>(id))) {
    const InputDef* d = cmd_->def().input(id.toStdString());
    const Unit length = parseUnit(session_.document().lengthUnit()).value_or(Unit::Millimeter);
    const Unit shown = d && dimensionOf(d->unit) == Dimension::Length ? length : (d ? d->unit : Unit::None);
    const QSignalBlocker block(sb);
    sb->setExpression(QString());
    sb->setValue(fromInternal(value, shown));
  }
  lastSent_[id.toStdString()] = value;
  onInputChanged(id.toStdString(), value);
}

bool CommandDialog::isEditingFeature() const { return cmd_->def().name.rfind("Edit ", 0) == 0; }

bool CommandDialog::setInputForTest(const QString& id, const QVariant& value) {
  QWidget* w = findChild<QWidget*>(id);
  if (auto* combo = qobject_cast<QComboBox*>(w)) {
    int i = combo->findText(value.toString());
    if (i < 0) i = combo->findData(value.toString());
    if (i < 0) return false;
    combo->setCurrentIndex(i);
    return true;
  }
  if (auto* sb = dynamic_cast<ExpressionSpinBox*>(w); sb && value.typeId() == QMetaType::QString) {
    sb->typeText(value.toString());
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
