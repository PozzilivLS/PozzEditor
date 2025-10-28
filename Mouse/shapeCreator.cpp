#include "shapeCreator.h"

#include <QMouseEvent>

#include "User/user.h"
#include "paintBoxModel.h"

void ShapeCreator::onMousePress(QMouseEvent* event) {
  currentShape_ = model_->addObj(User::getInstance()->ShapeCreatorType, event->pos());
  lastPos_ = event->pos();
  startPos_ = event->pos();
}

void ShapeCreator::onMouseMove(QMouseEvent* event) {
  QPoint diff = event->pos() - lastPos_;
  model_->resizeObj(const_cast<Shape*>( currentShape_), QSize(diff.x(), diff.y()));
  lastPos_ = event->pos();
}

void ShapeCreator::onMouseRelease(QMouseEvent* event) {}
