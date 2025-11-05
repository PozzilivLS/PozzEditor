#pragma once
#include "shape.h"

class Ellipse : public Shape {
 public:
  Ellipse(QPoint coordinates = QPoint(), QSize size = QSize(),
        QColor color = Qt::red);

  ShapeType type() const override { return ShapeType::Ellipse; }

  bool hasPointIn(QPoint point) const override;

  void draw(QPainter &painter) const override;
};
