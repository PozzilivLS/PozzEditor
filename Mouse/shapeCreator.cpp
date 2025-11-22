#include "shapeCreator.h"

#include <QHoverEvent>
#include <QMouseEvent>
#include <QRect>

#include "User/user.h"
#include "PaintBox/paintBoxModel.h"

void ShapeCreator::onMousePress(QMouseEvent* event) {
  startPos_ = event->pos();
  currentShape_ =
      model_->addObj(User::getInstance()->ShapeCreatorType, startPos_);
  lastPos_ = event->pos();
}

void ShapeCreator::onMouseMove(QMouseEvent* event) {
  if (!currentShape_) return;

  QPoint size = event->pos() - startPos_;

  QRect newObjSize(startPos_, QSize(size.x(), size.y()));

  QPoint outside = model_->isInWindow(newObjSize);
  if (outside.isNull()) {
    QPoint diff = event->pos() - lastPos_;
    model_->resizeObj(const_cast<Shape*>(currentShape_),
                      QSize(diff.x(), diff.y()));

    lastPos_ = event->pos();
  }
}

void ShapeCreator::onMouseRelease(QMouseEvent* event) {}

void ShapeCreator::onHoverMove(QHoverEvent* event) {}

void ShapeCreator::onHoverLeave(QHoverEvent* event) {}
