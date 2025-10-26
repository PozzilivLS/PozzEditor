#pragma once
#include <QPoint>

#include "mouse.h"

class PaintBoxModel;

class Brush : public Mouse {
 public:
  void onMousePress(QMouseEvent* event) override;
  void onMouseMove(QMouseEvent* event) override;

 private:
  QPoint lastPos_;
  int epsilon_ = 5;
};
