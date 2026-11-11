#pragma once
#include <QIcon>
#include <QString>

namespace tsr::app {

// Command and tool icons, painted in code (see Icons.cpp). Unknown names get
// a lettered tile so a new command is never invisible.
QIcon icon(const QString& name);
// Desktop theme icon (Breeze on KDE) if present, else our painted one.
QIcon themed(const QString& themeName, const QString& fallbackName);

} // namespace tsr::app
