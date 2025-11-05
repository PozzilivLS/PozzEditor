#pragma once

class QMouseEvent;
class PaintBoxModel;
class QHoverEvent;

class Mouse {
 public:
  void setModel(PaintBoxModel* model) { model_ = model; }
  virtual void onMousePress(QMouseEvent* event) = 0;
  virtual void onMouseMove(QMouseEvent* event) = 0;
  virtual void onMouseRelease(QMouseEvent* event) = 0;
  virtual void onHoverMove(QHoverEvent* event) = 0;
  virtual void onHoverLeave(QHoverEvent* event) = 0;
  virtual ~Mouse() {};

 protected:
  PaintBoxModel* model_;
};