#include "shape.h"

#include <QPainter>

Shape::~Shape() {}

Shape::Shape(QPoint coordinates, QSize size, QColor color)
    : pos_(coordinates), size_(size), color_(color) {
}

QColor Shape::getColor() const { return color_; }
void Shape::move(float x, float y) { pos_ = QPointF(x, y); }

void Shape::resize(float x, float y) {
  size_.setWidth(x);
  size_.setHeight(y);
}

void Shape::changeColor(QColor color) { color_ = color; }

QSizeF Shape::getSize() const { return size_; }

QPointF Shape::getPos() const { return pos_; }

QPointF Shape::getCentralPos() const {
  return pos_ + QPoint(size_.width() / 2, size_.height() / 2);
}

QRect Shape::getBounds() const { return QRect(pos_, size_); }
