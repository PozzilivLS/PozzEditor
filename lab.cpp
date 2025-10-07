#include "lab.h"
#include <QPainter>

Lab::Lab(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  paintBox_ = new PaintBox();

  paintBox_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  paintBox_->move(0, 0);
  ui.centralWidget->layout()->addWidget(paintBox_);
}

Lab::~Lab() {}
