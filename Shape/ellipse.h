#pragma once
#include "shape.h"
#include <QPainter>
class Ellipse : public Shape {
 public:
  Ellipse(QPoint coordinates = QPoint(), QSize size = QSize(),
        QColor color = Qt::red);

  ShapeType type() const override { return ShapeType::Ellipse; }

  bool hasPointIn(QPoint point) const override;
};
