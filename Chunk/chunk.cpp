#include "chunk.h"

void Chunk::addElement(CCircle* const& el) {
  Storage::addElement(el);

  QPoint luPoint = el->getPos();
  QPoint rdPoint = el->getPos() + QPoint(el->getRad() * 2, el->getRad() * 2);

  if (leftx_ > luPoint.x()) {
    leftx_ = luPoint.x();
  }
  if (upy_ > luPoint.y()) {
    upy_ = luPoint.y();
  }
  if (rightx < rdPoint.x()) {
    rightx = rdPoint.x();
  }
  if (downy_ < rdPoint.y()) {
    downy_ = rdPoint.y();
  }
}

bool Chunk::hasPointIn(QPoint point) const {
  return (point.x() > leftx_ && point.x() < rightx) &&
         (point.y() > upy_ && point.y() < downy_);
}

bool Chunk::isCircleInPoint(QPoint point) const {
  if (data_.size() == 0) {
    return false;
  }

  auto sqrMagnitude = [](QPoint a, QPoint b) {
    QPoint c = a - b;
    return c.x() * c.x() + c.y() * c.y();
  };

  int rad = data_[0]->getRad();
  for (const auto& circle : data_) {
    if (sqrMagnitude(point, circle->getPos()) <= rad) {
      return true;
    }
  }

  return false;
}
