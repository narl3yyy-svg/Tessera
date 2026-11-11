#pragma once
#include "tsr/core/Command.h"
#include "tsr/doc/Session.h"

#include <QDialog>

#include <memory>

class QLabel;
class QDialogButtonBox;
class QComboBox;

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

  // A body was clicked in the 3D view: fill the first body input, if any.
  bool pickBody(const QString& name);

  // Profiles picked in the 3D view (Extrude).
  bool hasProfilesInput() const;
  QString currentSketch() const;
  QString currentProfiles() const;
  void setProfiles(const QString& sketch, const QString& profiles);

  // Edges picked in the 3D view (Fillet, Chamfer).
  bool hasEdgesInput() const;
  QString currentEdges() const;
  QString currentBody() const;
  void setEdges(const QString& edges);

signals:
  void inputsChanged();

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
  QComboBox* bodyInput_ = nullptr;
  QComboBox* sketchInput_ = nullptr;
  QLabel* profilesLabel_ = nullptr;
  std::string profilesId_;
  QLabel* edgesLabel_ = nullptr;
  std::string edgesId_;
  void updateProfilesLabel();
};

} // namespace tsr::app
