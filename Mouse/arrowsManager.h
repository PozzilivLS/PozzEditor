#pragma once
#include "Mouse/mouse.h"

class Shape;
class Arrow;

class ArrowsManager : public Mouse {
 public:
  void onMousePress(QMouseEvent* event) override;
  void onMouseMove(QMouseEvent* event) override;
  void onMouseRelease(QMouseEvent* event) override;
  void onHoverMove(QHoverEvent* event) override;
  void onHoverLeave(QHoverEvent* event) override;

 private:
  Shape * startObj_ = nullptr;
  Arrow* createdArrow_ = nullptr;
};
