#include "rect.h"

Rect::Rect(QPoint coordinates, QSize size, QColor color)
    : Shape(coordinates, size, color) {}

bool Rect::hasPointIn(QPoint point) const {
  QRect r(pos_, size_);
  return r.contains(point);
}

void Rect::draw(QPainter& painter) const {
  QRect r(pos_, size_);
  painter.drawRect(r);
}
