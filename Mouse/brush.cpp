#include "brush.h"

#include <QMouseEvent>

#include "User/user.h"
#include "paintBoxModel.h"

void Brush::onMousePress(QMouseEvent* event) {
  model_->resetSelection();
  model_->createChunk();
  model_->addObj(event->pos());
  lastPos_ = event->pos();
}

void Brush::onMouseMove(QMouseEvent* event) {
  if (!User::getInstance()->SingleDrawing) {
    if ((lastPos_ - event->pos()).manhattanLength() >= epsilon_) {
      lastPos_ = event->pos();
      model_->addObj(event->pos());
    }
  }
}
