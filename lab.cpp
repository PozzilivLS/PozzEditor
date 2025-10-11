#include "lab.h"

#include <User/user.h>

#include <QPainter>

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

Lab::~Lab() {}

void Lab::setUpPaintBox() {
  paintBoxPresenter_ = new PaintBoxPresenter();
  paintBox_ = new PaintBox();

  paintBoxPresenter_->subscribeView(paintBox_);

  paintBox_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui.centralWidget->layout()->addWidget(paintBox_);

  paintBox_->show();
}

void Lab::brushSizeSliderValueChanged(int value) {
  User::getInstance()->BrushSize = value;
}

void Lab::cursorChoosed() {
  User::getInstance()->MouseType = MouseType::Cursor;
}

void Lab::brushChoosed() { User::getInstance()->MouseType = MouseType::Brush; }

void Lab::drawingModeChanged(Qt::CheckState state) {
  User::getInstance()->SingleDrawing = state == Qt::CheckState::Checked;
}
