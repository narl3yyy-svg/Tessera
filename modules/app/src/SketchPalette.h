#pragma once
#include <QDialog>
#include <QPointer>

class QCheckBox;
class QLabel;
class QToolButton;
class QWidget;

namespace tsr::app {

class SketchEditor;

// The SKETCH PALETTE panel shown in the canvas while a sketch is open:
// Feature Options for the current tool, display and grid options, Look At,
// Slice and Finish Sketch. It is a QDialog only for the panel styling; it is
// embedded in the canvas like the command panels.
class SketchPalette : public QDialog {
  Q_OBJECT
public:
  SketchPalette(SketchEditor* editor, QWidget* parent);

  // Reflect the editor's current tool and linetype.
  void sync();
  void setGrid(bool on, bool snap);
  bool sliceOn() const;

signals:
  void lookAtRequested();
  void sliceToggled(bool on);
  void gridToggled(bool on);
  void snapToggled(bool on);
  void finishRequested();

private:
  QToolButton* toolButton(const QString& name, const QString& icon, const QString& tip);
  QWidget* sectionHeader(const QString& title, QWidget* body);
  QCheckBox* option(const QString& name, const QString& label, bool on);
  void applyDisplay();

  QPointer<SketchEditor> editor_;
  QWidget* body_ = nullptr;
  QWidget* featureSection_ = nullptr;
  QLabel* featureLabel_ = nullptr;
  QToolButton* rect2_ = nullptr;
  QToolButton* rectCenter_ = nullptr;
  QToolButton* lineNormal_ = nullptr;
  QToolButton* lineConstruction_ = nullptr;
  QCheckBox* grid_ = nullptr;
  QCheckBox* snap_ = nullptr;
  QCheckBox* slice_ = nullptr;
  QCheckBox* profiles_ = nullptr;
  QCheckBox* points_ = nullptr;
  QCheckBox* dimensions_ = nullptr;
  QCheckBox* constraints_ = nullptr;
  QCheckBox* construction_ = nullptr;
};

} // namespace tsr::app
