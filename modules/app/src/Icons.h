#pragma once
#include "Theme.h"

#include <QIcon>
#include <QString>

class QAbstractButton;
class QAction;
class QObject;

namespace tsr::app {

// Command and tool icons, painted in code (see Icons.cpp) in the current
// theme's colours. Unknown names get a lettered tile.
QIcon icon(const QString& name);
// Desktop theme icon (Breeze on KDE) in the light theme if present; our
// painted one otherwise.
QIcon themed(const QString& themeName, const QString& fallbackName);

// Set an icon by name and remember it, so retintIcons() can repaint it after
// a theme change.
void setIcon(QAbstractButton* button, const QString& name);
void setIcon(QAction* action, const QString& name);
void retintIcons(QObject* root);

void setIconTheme(const Theme::Colors& colors);   // called by Theme::apply

} // namespace tsr::app
