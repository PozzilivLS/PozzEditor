#include "lab.h"
#include <QPainter>

Lab::Lab(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  paintBox_ = new PaintBox();

  paintBox_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui.centralWidget->layout()->addWidget(paintBox_);

  paintBox_->show();
}

Lab::~Lab() {}
