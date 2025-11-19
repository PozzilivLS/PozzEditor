#include "triangle.h"
#include <QPolygon>

Triangle::Triangle(QPoint coordinates, QSize size, QColor color)
    : Shape(coordinates, size, color) {}

bool Triangle::hasPointIn(QPoint point) const {
  QPolygon poly;
  poly << QPoint(pos_ + QPoint(0, size_.height()))
       << QPoint(pos_ + QPoint(size_.width(), size_.height()))
       << QPoint(pos_ + QPoint(size_.width() / 2, 0));
  return poly.containsPoint(point, Qt::OddEvenFill);
}

void Triangle::draw(QPainter& painter) const {
  QPolygon poly;
  poly << QPoint(pos_ + QPoint(0, size_.height()))
       << QPoint(pos_ + QPoint(size_.width(), size_.height()))
       << QPoint(pos_ + QPoint(size_.width() / 2, 0));

  painter.setBrush(color_);
  painter.drawPolygon(poly);
}
