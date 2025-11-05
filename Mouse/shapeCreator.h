#pragma once
#include "mouse.h"
#include <QPoint>

class Shape;

class ShapeCreator : public Mouse {
 public:
  void onMousePress(QMouseEvent* event) override;
  void onMouseMove(QMouseEvent* event) override;
  void onMouseRelease(QMouseEvent* event) override;
  void onHoverMove(QHoverEvent* event) override;
  void onHoverLeave(QHoverEvent* event) override;

 private:
  const Shape* currentShape_ = nullptr;
  QPoint startPos_;
  QPoint lastPos_;
};
