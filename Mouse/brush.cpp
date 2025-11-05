#include "brush.h"

#include <QMouseEvent>
#include <QHoverEvent>

#include "Chunk/chunk.h"
#include "User/user.h"
#include "paintBoxModel.h"

void Brush::onMousePress(QMouseEvent* event) {
  activeChunk_ = static_cast<Chunk*>(model_->addObj(ShapeType::Chunk));

  model_->createCircleInChunk(activeChunk_, event->pos());
  lastPos_ = event->pos();
}

void Brush::onMouseMove(QMouseEvent* event) {
  if ((lastPos_ - event->pos()).manhattanLength() >= epsilon_) {
    lastPos_ = event->pos();
    model_->createCircleInChunk(activeChunk_, event->pos());
  }
}

void Brush::onMouseRelease(QMouseEvent* event) { activeChunk_->setFixed(); }

void Brush::onHoverMove(QHoverEvent* event) {}

void Brush::onHoverLeave(QHoverEvent* event) {}
