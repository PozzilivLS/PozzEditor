#include "arrow.h"
#include "QDebug"

#include "Shape/shape.h"
#include <Shape/group.h>

Arrow::Arrow(Shape* from) : from_(from) { from_->addFromArrow(this); }

void Arrow::setFixed(Shape* to) {
  to_ = to;
  to_->addToArrow(this);
  isFixed_ = true;
}

void Arrow::addStorageObs(ArrowObserver* obs) { observers_.addElement(obs); }

void Arrow::moved(int dX, int dY) {
  if (isFixed_) {
    notifyStorageAboutMove(dX, dY);
  }
}

void Arrow::deleted(Shape * shape) {
  if (isFixed_)
    if (shape == from_) {
      notifyStorageAboutDeletion(ShapeType::From);
    } else if (shape == to_) {
      notifyStorageAboutDeletion(ShapeType::To);
    }
}

void Arrow::draw(QPainter& painter) const {
  painter.drawLine(from_->getCentralPos(),
                   isFixed_ ? to_->getCentralPos() : EndPointInCreationMode);

  QPolygonF arrowHead = createArrowHead();
  painter.drawPolygon(arrowHead);
}

bool Arrow::isPointIn(QPoint point) {
  if (!isFixed_) {
    return false;
  }

  if (isPointInArrow(point)) {
    return true;
  }

  return isPointInLine(point);
}

void Arrow::notifyStorageAboutDeletion(ShapeType type) {
  for (auto& obs : observers_) {
    obs->provideArrowDeletion(this, type);
  }
}

void Arrow::notifyStorageAboutMove(int dx, int dy) {
  for (auto& obs : observers_) {
    obs->provideArrowMove(to_, dx, dy);
  }
}

bool Arrow::isPointInLine(QPoint point) {
  QPoint lineVec = to_->getCentralPos() - from_->getCentralPos();

  double lineLengthSquared =
      lineVec.x() * lineVec.x() + lineVec.y() * lineVec.y();

  if (lineLengthSquared == 0) {
    return 0;
  }

  double t = std::max(0.0, std::min(1.0, QPoint::dotProduct(
                                      point - from_->getCentralPos(), lineVec) /
                                      lineLengthSquared));

  QPoint projection = from_->getCentralPos() + t * lineVec;

  QPoint diff = point - projection;
  int distanceSquared = diff.x() * diff.x() + diff.y() * diff.y();

  return distanceSquared <= ArrowSize * ArrowSize;
}

bool Arrow::isPointInArrow(QPoint point) {
  QPolygonF arrowHead = createArrowHead();

  return arrowHead.containsPoint(point, Qt::OddEvenFill);
}

QPolygonF Arrow::createArrowHead() const {
  QPointF direction =
      (isFixed_ ? to_->getCentralPos() : EndPointInCreationMode) -
      from_->getCentralPos();
  int length =
      std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

  if (length == 0) return QPolygon();

  direction /= length;
  QPointF perpendicular(-direction.y(), direction.x());

  QPointF arrowP1 = (isFixed_ ? to_->getCentralPos() : EndPointInCreationMode) -
                    direction * ArrowSize * 2 +
                                   perpendicular * ArrowSize;
  QPointF arrowP2 = (isFixed_ ? to_->getCentralPos()
                             : EndPointInCreationMode) - direction * ArrowSize * 2 -
                                   perpendicular * ArrowSize;

  QPolygonF arrowHead;
  arrowHead << (isFixed_ ? to_->getCentralPos() : EndPointInCreationMode) << arrowP1
            << arrowP2;

  return arrowHead;
}
