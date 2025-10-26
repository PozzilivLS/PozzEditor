#include "object.h"

#include <QPainter>

Object::~Object() {}

void Object::moveDiff(int x, int y) { pos_ += QPoint(x, y); }

void Object::resizeDiff(int x, int y) {
  size_.setWidth(size_.width() + x);
  size_.setHeight(size_.height() + x);
}

QSize Object::getSize() const { return size_; }

QPoint Object::getPos() const { return pos_; }

QPoint Object::getCentralPos() const {
  return pos_ + QPoint(size_.width() / 2, size_.height() / 2);
}

QColor Object::getColor() const { return color_; }

QRect Object::getBounds() const { return QRect(pos_, size_); }
