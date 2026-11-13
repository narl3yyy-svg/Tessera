#include "SketchPalette.h"
#include "Icons.h"
#include "SketchEditor.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QToolButton>
#include <QVBoxLayout>

namespace tsr::app {

using Tool = SketchEditor::Tool;

SketchPalette::SketchPalette(SketchEditor* editor, QWidget* parent) : QDialog(parent), editor_(editor) {
  setParent(parent, Qt::Widget);   // embedded in the canvas, not a window
  setObjectName(QStringLiteral("sketchPalette"));
  setProperty("panel", true);
  setAutoFillBackground(true);
  setMinimumWidth(250);

  auto* layout = new QVBoxLayout(this);
  layout->setContentsMargins(10, 6, 10, 8);
  layout->setSpacing(2);

  // Title row: "—" folds the palette away, like the familiar one.
  auto* titleRow = new QHBoxLayout;
  auto* fold = new QToolButton;
  fold->setObjectName(QStringLiteral("palette.fold"));
  fold->setText(QStringLiteral("—"));
  fold->setAutoRaise(true);
  fold->setToolTip(tr("Collapse or expand the palette"));
  auto* title = new QLabel(tr("SKETCH PALETTE"));
  title->setObjectName(QStringLiteral("panelTitle"));
  titleRow->addWidget(fold);
  titleRow->addWidget(title, 1);
  layout->addLayout(titleRow);

  body_ = new QWidget;
  auto* bodyLayout = new QVBoxLayout(body_);
  bodyLayout->setContentsMargins(0, 0, 0, 0);
  bodyLayout->setSpacing(2);
  layout->addWidget(body_);
  connect(fold, &QToolButton::clicked, this, [this] {
    body_->setVisible(!body_->isVisible());
    fit();
  });

  // Feature Options: the variants of the current tool.
  featureSection_ = new QWidget;
  {
    auto* g = new QGridLayout(featureSection_);
    g->setContentsMargins(14, 2, 0, 4);
    featureLabel_ = new QLabel(tr("Rectangle"));
    rect2_ = toolButton(QStringLiteral("palette.rect2pt"), QStringLiteral("rectangle"), tr("2-Point Rectangle"));
    rectCenter_ = toolButton(QStringLiteral("palette.rectCenter"), QStringLiteral("center-rectangle"), tr("Center Rectangle"));
    connect(rect2_, &QToolButton::clicked, this, [this] { if (editor_) editor_->setTool(Tool::Rectangle); sync(); });
    connect(rectCenter_, &QToolButton::clicked, this, [this] { if (editor_) editor_->setTool(Tool::CenterRectangle); sync(); });
    auto* buttons = new QHBoxLayout;
    buttons->addWidget(rect2_);
    buttons->addWidget(rectCenter_);
    buttons->addStretch();
    g->addWidget(featureLabel_, 0, 0);
    g->addLayout(buttons, 0, 1);
    g->setColumnStretch(0, 1);
  }
  bodyLayout->addWidget(sectionHeader(tr("Feature Options"), featureSection_));
  bodyLayout->addWidget(featureSection_);

  // Options.
  auto* options = new QWidget;
  auto* g = new QGridLayout(options);
  g->setContentsMargins(14, 2, 0, 4);
  g->setVerticalSpacing(4);
  g->setColumnStretch(0, 1);
  int row = 0;
  auto addRow = [&](const QString& label, QWidget* control) {
    g->addWidget(new QLabel(label), row, 0);
    g->addWidget(control, row, 1, Qt::AlignRight);
    ++row;
  };
  auto addRowLayout = [&](const QString& label, QLayout* control) {
    g->addWidget(new QLabel(label), row, 0);
    g->addLayout(control, row, 1, Qt::AlignRight);
    ++row;
  };

  lineNormal_ = toolButton(QStringLiteral("palette.linetypeNormal"), QStringLiteral("line"), tr("Normal geometry"));
  lineConstruction_ = toolButton(QStringLiteral("palette.linetypeConstruction"), QStringLiteral("construction"),
                                 tr("Construction geometry (X): reference only, never a profile"));
  connect(lineNormal_, &QToolButton::clicked, this, [this] { if (editor_) editor_->setConstruction(false); sync(); });
  connect(lineConstruction_, &QToolButton::clicked, this, [this] { if (editor_) editor_->setConstruction(true); sync(); });
  auto* linetype = new QHBoxLayout;
  linetype->addWidget(lineNormal_);
  linetype->addWidget(lineConstruction_);
  addRowLayout(tr("Linetype"), linetype);

  auto* lookAt = toolButton(QStringLiteral("palette.lookAt"), QStringLiteral("look-at"), tr("Look straight at the sketch plane"));
  lookAt->setCheckable(false);
  connect(lookAt, &QToolButton::clicked, this, &SketchPalette::lookAtRequested);
  addRow(tr("Look At"), lookAt);

  grid_ = option(QStringLiteral("palette.grid"), tr("Sketch Grid"), true);
  snap_ = option(QStringLiteral("palette.snap"), tr("Snap"), false);
  slice_ = option(QStringLiteral("palette.slice"), tr("Slice"), false);
  slice_->setToolTip(tr("Cut away the bodies in front of the sketch plane"));
  profiles_ = option(QStringLiteral("palette.profiles"), tr("Profile"), true);
  points_ = option(QStringLiteral("palette.points"), tr("Points"), true);
  dimensions_ = option(QStringLiteral("palette.dimensions"), tr("Dimensions"), true);
  constraints_ = option(QStringLiteral("palette.constraints"), tr("Constraints"), true);
  projected_ = option(QStringLiteral("palette.projected"), tr("Projected Geometries"), true);
  projected_->setToolTip(tr("Body edges and corners copied into the sketch when you snap to them (purple)"));
  QCheckBox* projected = projected_;
  construction_ = option(QStringLiteral("palette.construction"), tr("Construction Geometries"), true);
  auto* sketch3d = option(QStringLiteral("palette.3d"), tr("3D Sketch"), false);
  sketch3d->setEnabled(false);
  sketch3d->setToolTip(tr("Planned: see docs/ROADMAP.md"));
  for (QCheckBox* c : {grid_, snap_, slice_, profiles_, points_, dimensions_, constraints_, projected, construction_, sketch3d})
    addRow(c->accessibleName(), c);

  connect(grid_, &QCheckBox::toggled, this, &SketchPalette::gridToggled);
  connect(snap_, &QCheckBox::toggled, this, &SketchPalette::snapToggled);
  connect(slice_, &QCheckBox::toggled, this, &SketchPalette::sliceToggled);
  for (QCheckBox* c : {profiles_, points_, dimensions_, constraints_, construction_, projected_})
    connect(c, &QCheckBox::toggled, this, [this] { applyDisplay(); });

  bodyLayout->addWidget(sectionHeader(tr("Options"), options));
  bodyLayout->addWidget(options);

  auto* finish = new QPushButton(tr("Finish Sketch"));
  finish->setObjectName(QStringLiteral("palette.finish"));
  connect(finish, &QPushButton::clicked, this, &SketchPalette::finishRequested);
  auto* finishRow = new QHBoxLayout;
  finishRow->addStretch();
  finishRow->addWidget(finish);
  bodyLayout->addLayout(finishRow);

  if (editor_) {
    const auto& d = editor_->display();
    for (auto [box, on] : {std::pair{profiles_, d.profiles}, {points_, d.points}, {dimensions_, d.dimensions},
                           {constraints_, d.constraints}, {construction_, d.construction}}) {
      const QSignalBlocker b(box);
      box->setChecked(on);
    }
  }
  sync();
}

QToolButton* SketchPalette::toolButton(const QString& name, const QString& iconName, const QString& tip) {
  auto* b = new QToolButton;
  b->setObjectName(name);
  setIcon(b, iconName);
  b->setIconSize(QSize(20, 20));
  b->setCheckable(true);
  b->setAutoRaise(true);
  b->setToolTip(tip);
  b->setAccessibleName(tip);
  return b;
}

QWidget* SketchPalette::sectionHeader(const QString& title, QWidget* body) {
  auto* h = new QToolButton;
  h->setText(title);
  h->setObjectName(QStringLiteral("palette.section"));
  h->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  h->setArrowType(Qt::DownArrow);
  h->setAutoRaise(true);
  QFont f = h->font();
  f.setBold(true);
  h->setFont(f);
  connect(h, &QToolButton::clicked, this, [this, h, body] {
    const bool show = !body->isVisible();
    body->setVisible(show);
    h->setArrowType(show ? Qt::DownArrow : Qt::RightArrow);
    fit();
  });
  return h;
}

QCheckBox* SketchPalette::option(const QString& name, const QString& label, bool on) {
  auto* c = new QCheckBox;
  c->setObjectName(name);
  c->setAccessibleName(label);
  c->setChecked(on);
  return c;
}

void SketchPalette::applyDisplay() {
  if (!editor_) return;
  SketchEditor::Display d;
  d.profiles = profiles_->isChecked();
  d.points = points_->isChecked();
  d.dimensions = dimensions_->isChecked();
  d.constraints = constraints_->isChecked();
  d.construction = construction_->isChecked();
  d.projected = projected_->isChecked();
  editor_->setDisplay(d);
}

void SketchPalette::sync() {
  if (!editor_) return;
  const Tool t = editor_->tool();
  const bool rect = t == Tool::Rectangle || t == Tool::CenterRectangle;
  featureSection_->setVisible(rect);
  // The section header sits right before the section.
  if (auto* lay = body_->layout())
    for (int i = 0; i + 1 < lay->count(); ++i)
      if (lay->itemAt(i + 1)->widget() == featureSection_ && lay->itemAt(i)->widget())
        lay->itemAt(i)->widget()->setVisible(rect);
  rect2_->setChecked(t == Tool::Rectangle);
  rectCenter_->setChecked(t == Tool::CenterRectangle);
  lineNormal_->setChecked(!editor_->construction());
  lineConstruction_->setChecked(editor_->construction());
  fit();
}

void SketchPalette::fit() {
  if (body_ && body_->layout()) body_->layout()->activate();
  if (layout()) layout()->activate();
  adjustSize();
  // Once Qt has laid out what was shown or hidden, fit again.
  QTimer::singleShot(0, this, [this] {
    if (layout()) layout()->activate();
    adjustSize();
  });
}

void SketchPalette::setGrid(bool on, bool snap) {
  const QSignalBlocker a(grid_), b(snap_);
  grid_->setChecked(on);
  snap_->setChecked(snap);
}

bool SketchPalette::sliceOn() const { return slice_->isChecked(); }

} // namespace tsr::app
