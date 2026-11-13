#pragma once
#include "tsr/doc/Session.h"

#include <QDialog>
#include <QMap>
#include <QPair>
#include <QPoint>

class QLabel;
class QLineEdit;
class QTreeWidget;
class QTreeWidgetItem;

namespace tsr::app {

// Modify > Change Parameters, as in the familiar dialog: a star (favourite),
// the parameter, its name, unit, expression, value and comment. Favorites
// first, then the user parameters, then the model parameters per feature
// (sketch dimensions and feature values: d1, d2 ...). Double-click a name to
// rename it (users of it follow) or an expression to change it; each change
// is one undo step. The filter box narrows the table.
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
  void setFilterForTest(const QString& text);
  int visibleParameterRows() const;   // leaf rows the filter leaves showing
  // Live tests: each parameter's star and name cells (global), when shown.
  QMap<QString, QPair<QPoint, QPoint>> rowPoints() const;

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
  void applyFilter();

  doc::Session& session_;
  QTreeWidget* tree_ = nullptr;
  QLabel* error_ = nullptr;
  QLineEdit* filter_ = nullptr;
  int listener_ = 0;
  bool building_ = false;
  bool rebuildPending_ = false;
};

} // namespace tsr::app
