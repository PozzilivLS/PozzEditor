#include "brush.h"

#include <QMouseEvent>
#include <QHoverEvent>

#include "Chunk/chunk.h"
#include "User/user.h"
#include "PaintBox/paintBoxModel.h"

void Brush::onMousePress(QMouseEvent* event) {
  activeChunk_ = static_cast<Chunk*>(model_->addObj("Chunk"));
  if (!activeChunk_) return;

  model_->createCircleInChunk(activeChunk_, event->pos());
  lastPos_ = event->pos();
}

void Brush::onMouseMove(QMouseEvent* event) {
  if (!activeChunk_) return;

  if ((lastPos_ - event->pos()).manhattanLength() >= epsilon_) {
    lastPos_ = event->pos();
    model_->createCircleInChunk(activeChunk_, event->pos());
  }
}

void Brush::onMouseRelease(QMouseEvent* event) {
  if (!activeChunk_) return;
  activeChunk_->setFixed();
}

void Brush::onHoverMove(QHoverEvent* event) {}

void Brush::onHoverLeave(QHoverEvent* event) {}
