#pragma once
#include "tsr/doc/Session.h"

#include <QDialog>

class QLabel;
class QTreeWidget;
class QTreeWidgetItem;

namespace tsr::app {

// Modify > Change Parameters: one table with the user parameters (name, unit,
// expression, value, comment; add and delete) and, per feature, its numeric
// inputs as model parameters. Every expression cell is editable; a change is
// one undo step and the model recomputes at once.
class ParametersDialog : public QDialog {
  Q_OBJECT
public:
  ParametersDialog(doc::Session& session, QWidget* parent = nullptr);
  ~ParametersDialog() override;

  // For scripted GUI tests. `parameter` is a user parameter's name or
  // "<Feature>.<input id>" for a model parameter.
  bool setExpressionForTest(const QString& parameter, const QString& expression);
  QString errorText() const;
  QTreeWidget* table() const { return tree_; }

  // Adds a user parameter as the "+" form would. Returns empty or the error.
  QString addParameter(const QString& name, const QString& unit, const QString& expression, const QString& comment);

private:
  void rebuild();
  void scheduleRebuild();
  void onItemChanged(QTreeWidgetItem* item, int column);
  void showAddForm();
  void deleteSelected();
  void showError(const QString& text);
  QTreeWidgetItem* findRow(const QString& parameter) const;

  doc::Session& session_;
  QTreeWidget* tree_ = nullptr;
  QLabel* error_ = nullptr;
  int listener_ = 0;
  bool building_ = false;
  bool rebuildPending_ = false;
};

} // namespace tsr::app
