#include "ParameterCompleter.h"

#include <QAbstractItemView>
#include <QCompleter>
#include <QKeyEvent>
#include <QLineEdit>
#include <QStringListModel>

namespace tsr::app {

void ParameterCompleter::attach(QLineEdit* edit, Names names) {
  if (!edit || edit->property("parameterCompleter").toBool()) return;
  edit->setProperty("parameterCompleter", true);
  new ParameterCompleter(edit, std::move(names));
}

ParameterCompleter::ParameterCompleter(QLineEdit* edit, Names names)
    : QObject(edit), edit_(edit), names_(std::move(names)), completer_(new QCompleter(this)) {
  completer_->setModel(new QStringListModel(completer_));
  completer_->setCaseSensitivity(Qt::CaseInsensitive);
  completer_->setCompletionMode(QCompleter::PopupCompletion);
  completer_->setWidget(edit_);
  completer_->popup()->setObjectName(QStringLiteral("parameterSuggestions"));
  connect(edit_, &QLineEdit::textEdited, this, &ParameterCompleter::onEdited);
  connect(completer_, qOverload<const QString&>(&QCompleter::activated), this, &ParameterCompleter::insert);
  // Enter / Tab in the list takes the name and stops there; the next Enter
  // applies the value (the list must not pass the first one to the box).
  completer_->popup()->installEventFilter(this);
}

bool ParameterCompleter::eventFilter(QObject* watched, QEvent* e) {
  if (watched == completer_->popup() && e->type() == QEvent::KeyPress) {
    const int key = static_cast<QKeyEvent*>(e)->key();
    if (key == Qt::Key_Return || key == Qt::Key_Enter || key == Qt::Key_Tab) {
      const QModelIndex i = completer_->popup()->currentIndex();
      const QString name = i.isValid() ? i.data().toString() : completer_->currentCompletion();
      completer_->popup()->hide();
      if (!name.isEmpty()) insert(name);
      return true;
    }
  }
  return QObject::eventFilter(watched, e);
}

bool ParameterCompleter::currentWord(int& start, QString& prefix) const {
  const QString t = edit_->text();
  const int end = edit_->cursorPosition();
  start = end;
  while (start > 0 && (t[start - 1].isLetterOrNumber() || t[start - 1] == QLatin1Char('_'))) --start;
  prefix = t.mid(start, end - start);
  // A word, not a number ("12" or "3.5").
  return !prefix.isEmpty() && (prefix[0].isLetter() || prefix[0] == QLatin1Char('_'));
}

void ParameterCompleter::onEdited(const QString&) {
  int start = 0;
  QString prefix;
  const QStringList names = names_ ? names_() : QStringList();
  if (names.isEmpty() || !currentWord(start, prefix)) {
    completer_->popup()->hide();
    return;
  }
  static_cast<QStringListModel*>(completer_->model())->setStringList(names);
  completer_->setCompletionPrefix(prefix);
  if (completer_->completionCount() == 0 ||
      (completer_->completionCount() == 1 && completer_->currentCompletion().compare(prefix, Qt::CaseInsensitive) == 0)) {
    completer_->popup()->hide();
    return;
  }
  completer_->complete();
}

void ParameterCompleter::insert(const QString& name) {
  int start = 0;
  QString prefix;
  if (!currentWord(start, prefix)) return;
  QString t = edit_->text();
  t.replace(start, prefix.size(), name);
  edit_->setText(t);
  edit_->setCursorPosition(start + static_cast<int>(name.size()));
}

} // namespace tsr::app
