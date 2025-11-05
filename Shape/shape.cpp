#include "shape.h"

#include <QPainter>

Shape::~Shape() {}

Shape::Shape(QPoint coordinates, QSize size, QColor color)
    : pos_(coordinates), size_(size), color_(color) {
}

QColor Shape::getColor() const { return color_; }
void Shape::move(int x, int y) { pos_ = QPoint(x, y); }

void Shape::resize(int x, int y) {
  size_.setWidth(x);
  size_.setHeight(y);
}

void Shape::changeColor(QColor color) { color_ = color; }

QSize Shape::getSize() const { return size_; }

QPoint Shape::getPos() const { return pos_; }

QPoint Shape::getCentralPos() const {
  return pos_ + QPoint(size_.width() / 2, size_.height() / 2);
}

QRect Shape::getBounds() const { return QRect(pos_, size_); }
