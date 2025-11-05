#pragma once
#include "shape.h"
class Rect : public Shape {
 public:
  Rect(QPoint coordinates = QPoint(), QSize size = QSize(),
          QColor color = Qt::red);

  ShapeType type() const override { return ShapeType::Rect; }

  bool hasPointIn(QPoint point) const override;

  void draw(QPainter &painter) const override;
};
