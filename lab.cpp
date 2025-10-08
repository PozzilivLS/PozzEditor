#include "lab.h"
#include <QPainter>

Lab::Lab(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  paintBoxPresenter_ = new PaintBoxPresenter();
  paintBox_ = new PaintBox();

  paintBoxPresenter_->subscribeView(paintBox_);

  paintBox_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui.centralWidget->layout()->addWidget(paintBox_);

  paintBox_->show();
}

Lab::~Lab() {}
