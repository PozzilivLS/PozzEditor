#include "chunk.h"

#include <QDebug>
#include <QPoint>
#include <QBitmap>

Chunk::Chunk(QColor color) : Shape(QPoint(), QSize(), color) {}

Chunk::~Chunk() {
  for (auto& obj : data_) {
    delete obj;
  }
}

void Chunk::addElement(Ellipse* const& el) {
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
  cache_ = QPixmap(size_ + QSize(pos_.x(), pos_.y()));
  mask_ = QBitmap(cache_.size());
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

  int rad = data_[0]->getSize().height() / 2;
  for (const auto& circle : data_) {
    if (sqrMagnitude(point, circle->getCentralPos()) <= rad * rad) {
      return true;
    }
  } // TODO: incaps?

  return false;
}

void Chunk::changeColor(QColor color) {
  color_ = color;
  for (const auto& el : data_) {
    el->changeColor(color);
  }
}

QPixmap& Chunk::getPixmap() { return cache_; }

const QPixmap& Chunk::getPixmap() const { return cache_; }

bool Chunk::isFixed() const { return isFixed_; }

void Chunk::setFixed() { isFixed_ = true; }
