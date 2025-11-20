#pragma once
#include "shape.h"
class Triangle : public Shape {
 public:
  Triangle(QPoint coordinates = QPoint(), QSize size = QSize(),
       QColor color = Qt::red);

  const char* type() const override { return "Triangle"; }

  bool hasPointIn(QPoint point) const override;

  void draw(QPainter &painter) const override;
};
