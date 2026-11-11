#include "CommandDialog.h"

#include <QCheckBox>
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

  auto* form = new QFormLayout;
  for (const InputDef& in : def.inputs) {
    const QString label = QString::fromStdString(in.label);
    const QString tip = QString::fromStdString(in.tooltip);
    const Value& cur = cmd_->inputs().at(in.id);
    QWidget* w = nullptr;
    const std::string id = in.id;

    switch (in.type) {
      case InputType::Real: {
        auto* sb = new QDoubleSpinBox;
        sb->setDecimals(3);
        const double step = fromInternal(1.0, in.unit) / 10.0; // 1 mm for mm inputs
        sb->setSingleStep(step > 0 ? step : 1.0);
        double lo = in.min ? fromInternal(*in.min, in.unit) : -1e9;
        if (in.min && in.minExclusive) lo += std::pow(10.0, -sb->decimals());
        sb->setRange(lo, in.max ? fromInternal(*in.max, in.unit) : 1e9);
        if (in.unit != Unit::None) sb->setSuffix(QStringLiteral(" ") + QString::fromUtf8(unitSymbol(in.unit).data()));
        if (auto p = std::get_if<double>(&cur)) sb->setValue(fromInternal(*p, in.unit));
        const Unit unit = in.unit;
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
    }
    w->setObjectName(QString::fromStdString(in.id));
    w->setToolTip(tip);
    w->setAccessibleName(label);
    form->addRow(label, w);
  }

  error_ = new QLabel;
  error_->setObjectName(QStringLiteral("error"));
  error_->setWordWrap(true);
  error_->setStyleSheet(QStringLiteral("color: palette(highlight);"));
  buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  connect(buttons_, &QDialogButtonBox::accepted, this, &CommandDialog::accept);
  connect(buttons_, &QDialogButtonBox::rejected, this, &CommandDialog::reject);

  auto* layout = new QVBoxLayout(this);
  layout->addLayout(form);
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

void CommandDialog::refreshPreview() {
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

bool CommandDialog::setInputForTest(const QString& id, const QVariant& value) {
  QWidget* w = findChild<QWidget*>(id);
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
