#include "ellipse.h"

#include <QPainter>

Ellipse::Ellipse(QPoint coordinates, QSize size, QColor color)
    : Shape(coordinates, size, color) {}

bool Ellipse::hasPointIn(QPoint point) const {
  QPointF left = pos_ + QPointF(0, size_.height() / 2.0);
  QPointF right = pos_ + QPointF(size_.width(), size_.height() / 2.0);
  QPointF up = pos_ + QPointF(size_.width() / 2.0, 0);
  QPointF down = pos_ + QPointF(size_.width() / 2.0, size_.height());

  int xc = up.x(), yc = left.y();
  float a = abs(right.x() - left.x()) / 2.0;
  float b = abs(down.y() - up.y()) / 2.0;

  float E = ((point.x() - xc) * (point.x() - xc)) / (a * a) +
            ((point.y() - yc) * (point.y() - yc)) / (b * b);
  return E <= 1;
}

void Ellipse::draw(QPainter &painter) const {
  QRect r(pos_, size_);

  painter.setBrush(color_);
  painter.drawEllipse(r);
}
