#include "ellipse.h"

Ellipse::Ellipse(QPoint coordinates, QSize size, QColor color)
    : Shape(coordinates, size, color) {}

bool Ellipse::hasPointIn(QPoint point) const {
  auto sqrMagnitude = [](QPoint a, QPoint b) {
    QPoint c = a - b;
    return c.x() * c.x() + c.y() * c.y();
  };
  int rad = size_.height() / 2;

  if (sqrMagnitude(point, getCentralPos()) <= rad * rad) {
    return true;
  }
  return false;
}
