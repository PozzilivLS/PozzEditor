#pragma once
#include <QPoint>
#include "Selection/selection.h"

#include "mouse.h"

class PaintBoxModel;

class Cursor : public Mouse {
 public:
  void onMousePress(QMouseEvent* event) override;
  void onMouseMove(QMouseEvent* event) override;
  void onMouseRelease(QMouseEvent* event) override;
  void onHoverMove(QHoverEvent* event) override;
  void onHoverLeave(QHoverEvent* event) override;
 
 private:
  QPoint lastPos_;
  Selection::MousePosState sizeChangeState_ = Selection::MousePosState::None;
  bool isChanging_ = false;
};
