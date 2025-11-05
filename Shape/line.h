#pragma once
#include "shape.h"
class Line : public Shape {
 public:
  Line(QPoint coordinates = QPoint(), QSize size = QSize(),
          QColor color = Qt::red);

  ShapeType type() const override { return ShapeType::Line; }

  bool hasPointIn(QPoint point) const override;
  QRect getBounds() const override;

  void draw(QPainter &painter) const override;

  int getLineSize();

 private:
  int lineSize_ = 0;
};
