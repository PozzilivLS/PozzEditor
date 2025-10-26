#include "chunk.h"

#include <QDebug>
#include <QPoint>
#include <QBitmap>

Chunk::~Chunk() {
  for (auto& obj : data_) {
    delete obj;
  }
}

void Chunk::addElement(Object* const& el) {
  Storage::addElement(el);

  QPoint luPoint = el->getPos();
  QPoint rdPoint =
      el->getPos() + QPoint(el->getSize().width(), el->getSize().height());

  if (size() == 1) {
    pos_ = el->getPos();
    size_ = el->getSize();
  }

  QRect rect(pos_, size_);
  rect = rect.united(QRect(luPoint, rdPoint));
  pos_ = rect.topLeft();
  size_ = rect.size();

  // TODO: refactor
  cache_ = QPixmap(size_);
  mask_ = QBitmap(size_);
  mask_.clear();
  cache_.setMask(mask_);
}

bool Chunk::hasPointIn(QPoint point) const {
  QRect rect(pos_, size_);
  if (!rect.contains(point)) {
    return false;
  }

  return isCircleInPoint(point);
}

bool Chunk::isCircleInPoint(QPoint point) const {
  if (size() == 0) {
    return false;
  }

  auto sqrMagnitude = [](QPoint a, QPoint b) {
    QPoint c = a - b;
    return c.x() * c.x() + c.y() * c.y();
  };

  //int rad = data_[0]->getRad();
  for (const auto& circle : data_) {
    if (sqrMagnitude(point, circle->getCentralPos()) <= rad * rad) {
      return true;
    }
  }

  return false;
}

QPixmap& Chunk::getPixmap() { return cache_; }

const QPixmap& Chunk::getPixmap() const { return cache_; }
