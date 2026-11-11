#pragma once
#include "tsr/core/Command.h"
#include "tsr/doc/Session.h"

#include <QDialog>

#include <memory>

class QLabel;
class QDialogButtonBox;

namespace tsr::app {

// A dialog generated entirely from CommandDef::inputs. Every edit updates the
// CommandSession and re-runs the preview; OK executes, Cancel rolls back.
class CommandDialog : public QDialog {
  Q_OBJECT
public:
  CommandDialog(doc::Session& session, std::unique_ptr<CommandSession> cmd, QWidget* parent = nullptr);
  ~CommandDialog() override;

  // For scripted GUI tests: set an input by id as the user would.
  bool setInputForTest(const QString& id, const QVariant& value);

public slots:
  void accept() override;
  void reject() override;

private:
  void onInputChanged(const std::string& id, const Value& v);
  void refreshPreview();
  void showError(const std::string& err);

  doc::Session& session_;
  std::unique_ptr<CommandSession> cmd_;
  QLabel* error_ = nullptr;
  QDialogButtonBox* buttons_ = nullptr;
};

} // namespace tsr::app
