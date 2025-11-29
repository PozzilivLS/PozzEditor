#include "arrowsManager.h"

#include <QMouseEvent>
#include <QDebug>

#include "PaintBox/paintBoxModel.h"
#include "Shape/shape.h"

void ArrowsManager::onMousePress(QMouseEvent *event) {
  if (model_->selectArrow(event->pos())) {
    return;
  }

  startObj_ = model_->chooseTopObject(event->pos());
  if (startObj_) {
    createdArrow_ = model_->createArrow(startObj_);
    model_->moveArrowEnd(createdArrow_, event->pos());
  }
}

void ArrowsManager::onMouseMove(QMouseEvent *event) {
  if (!createdArrow_) return;
  model_->moveArrowEnd(createdArrow_, event->pos());
}

void ArrowsManager::onMouseRelease(QMouseEvent *event) {
  if (!createdArrow_) return;
  Shape *endObj = model_->chooseTopObject(event->pos());

  if (startObj_ && endObj && model_->tryToFixArrow(createdArrow_, endObj)) {

  } else if (startObj_) {
    model_->deleteArrow(createdArrow_);
    createdArrow_ = nullptr;
  }
  startObj_ = nullptr;
}

void ArrowsManager::onHoverMove(QHoverEvent *event) {}

void ArrowsManager::onHoverLeave(QHoverEvent *event) {}
