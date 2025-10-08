#include "lab.h"
#include <QPainter>
#include <User/user.h>

Lab::Lab(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  connect(ui.brushSizeSlider, SIGNAL(valueChanged(int)),
          SLOT(brushSizeSliderValueChanged(int)));

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
