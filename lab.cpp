#include "lab.h"

#include <QKeyEvent>
#include <QPainter>

#include "Mouse/brush.h"
#include "Mouse/cursor.h"
#include "PaintBox/paintbox.h"
#include "User/user.h"
#include "paintBoxPresenter.h"

Lab::Lab(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  connect(ui.brushSizeSlider, SIGNAL(valueChanged(int)),
          SLOT(brushSizeSliderValueChanged(int)));
  connect(ui.chooseMouseBtn, SIGNAL(clicked()), SLOT(cursorChoosed()));
  connect(ui.chooseBrushBtn, SIGNAL(clicked()), SLOT(brushChoosed()));
  connect(ui.singleObjDrawingButton, SIGNAL(checkStateChanged(Qt::CheckState)),
          SLOT(drawingModeChanged(Qt::CheckState)));

  setUpPaintBox();
}

Lab::~Lab() {
  if (paintBoxPresenter_) delete paintBoxPresenter_;
  if (paintBox_) delete paintBox_;
  if (brush_) delete brush_;
  if (cursor_) delete cursor_;
}

void Lab::setUpPaintBox() {
  paintBoxPresenter_ = new PaintBoxPresenter();
  paintBox_ = new PaintBox();

  paintBoxPresenter_->subscribeView(paintBox_);

  paintBox_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui.centralWidget->layout()->addWidget(paintBox_);

  paintBox_->show();

  brush_ = new Brush();
  cursor_ = new Cursor();
  paintBoxPresenter_->setMouseType(cursor_);
}

void Lab::brushSizeSliderValueChanged(int value) {
  User::getInstance()->BrushSize = value;
}

void Lab::cursorChoosed() { paintBoxPresenter_->setMouseType(cursor_); }

void Lab::brushChoosed() { paintBoxPresenter_->setMouseType(brush_); }

void Lab::drawingModeChanged(Qt::CheckState state) {
  User::getInstance()->SingleDrawing = state == Qt::CheckState::Checked;
}
