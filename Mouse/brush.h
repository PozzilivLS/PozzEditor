#pragma once
#include <QPoint>

#include "mouse.h"

class PaintBoxModel;
class Chunk;

class Brush : public Mouse {
 public:
  void onMousePress(QMouseEvent* event) override;
  void onMouseMove(QMouseEvent* event) override;
  void onMouseRelease(QMouseEvent* event) override;
  void onHoverMove(QHoverEvent* event) override;
  void onHoverLeave(QHoverEvent* event) override;

 private:
  Chunk* activeChunk_ = nullptr;

  QPoint lastPos_;
  int epsilon_ = 5;
};
