#pragma once
#include <QObject>
#include <QStringList>

#include <functional>

class QCompleter;
class QLineEdit;

namespace tsr::app {

// Suggests parameter names while a value is typed, as the familiar tool does:
// type "wi" in "wi / 2" and "width" is offered; picking it replaces the word
// being typed. `names` is asked each time, so new parameters show up.
class ParameterCompleter final : public QObject {
  Q_OBJECT
public:
  using Names = std::function<QStringList()>;
  // Attaches to `edit` (once; later calls do nothing).
  static void attach(QLineEdit* edit, Names names);

protected:
  bool eventFilter(QObject* watched, QEvent* e) override;

private:
  ParameterCompleter(QLineEdit* edit, Names names);
  void onEdited(const QString& text);
  void insert(const QString& name);
  // The identifier being typed: its start in the text, and the prefix.
  bool currentWord(int& start, QString& prefix) const;

  QLineEdit* edit_;
  Names names_;
  QCompleter* completer_;
};

} // namespace tsr::app
