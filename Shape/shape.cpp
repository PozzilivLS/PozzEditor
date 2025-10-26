#include "shape.h"

Shape::Shape(QPoint coordinates, QSize size, QColor color)
    : Object(), color_(color) {
  pos_ = coordinates;
  size_ = size;
}

QColor Shape::getColor() const { return color_; };