#pragma once
#include <QPoint>

#include "mouse.h"

class PaintBoxModel;

class Cursor : public Mouse {
 public:
  void onMousePress(QMouseEvent* event) override;
  void onMouseMove(QMouseEvent* event) override;
};
