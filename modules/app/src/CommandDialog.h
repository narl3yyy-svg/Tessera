#pragma once
#include "tsr/core/Command.h"
#include "tsr/doc/Session.h"

#include <QDialog>

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class QLabel;
class QDialogButtonBox;
class QComboBox;
class QFormLayout;

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

  // Faces (Shell) and tool bodies (Combine) picked in the 3D view.
  bool hasFacesInput() const;
  bool hasBodiesInput() const;
  QString currentFaces() const;
  QString currentTools() const;
  void setFaces(const QString& faces);
  void setTools(const QString& bodies);

  // A plane clicked in the canvas fills the first plane input.
  bool hasPlaneInput() const;
  void pickPlane(const QString& spec, const QString& label);

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
  QComboBox* planeInput_ = nullptr;
  QLabel* profilesLabel_ = nullptr;
  std::string profilesId_;
  QLabel* edgesLabel_ = nullptr;
  std::string edgesId_;
  QLabel* facesLabel_ = nullptr;
  std::string facesId_;
  QLabel* bodiesLabel_ = nullptr;
  std::string bodiesId_;
  QString stringInput(const std::string& id) const;
  void updateVisibility();
  void adjustAfterResize();
  QFormLayout* form_ = nullptr;
  std::vector<std::pair<QWidget*, std::string>> conditional_;
  void updateProfilesLabel();
  std::map<std::string, Value> lastSent_;   // last value each numeric field sent
};

} // namespace tsr::app
