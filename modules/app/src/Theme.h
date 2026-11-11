#pragma once
// Application colour theme. Dark (default) follows the look of mainstream CAD
// tools: charcoal panels, a dark slate canvas, light text and icons. Light is
// the original bright look. The choice is saved; TSR_THEME=dark|light
// overrides it (tests, screenshots).
#include <QColor>
#include <QObject>

namespace tsr::app {

class Theme final : public QObject {
  Q_OBJECT
public:
  enum class Mode { Dark, Light };

  struct Colors {
    // Widgets
    QColor window, panel, base, text, mutedText, border, highlight;
    // Icons
    QColor iconLine, iconTop, iconLeft, iconRight, iconAccent;
    // Canvas
    QColor viewTop, viewBottom, grid, gridMajor, cubeBox, cubeText, edges, overlayText;
    // Sketches
    QColor sketchFree, sketchFixed, sketchLabel, sketchGlyph, sketchFinished;
    // Navigation bar and timeline
    QColor navBackground, navBorder, errorBackground;
  };

  static Theme& instance();
  static Mode saved();

  Mode mode() const { return mode_; }
  bool dark() const { return mode_ == Mode::Dark; }
  const Colors& colors() const { return colors_; }

  // Applies palette, style sheet and colours to the whole application.
  void apply(Mode m, bool save = true);

signals:
  void changed();

private:
  Theme() = default;
  Mode mode_ = Mode::Dark;
  Colors colors_{};
  bool styled_ = false;
};

inline const Theme::Colors& themeColors() { return Theme::instance().colors(); }

} // namespace tsr::app
