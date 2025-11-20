#pragma once
#include "shape.h"
class Rect : public Shape {
 public:
  Rect(QPoint coordinates = QPoint(), QSize size = QSize(),
          QColor color = Qt::red);

  const char* type() const override { return "Rect"; }

  bool hasPointIn(QPoint point) const override;

  void draw(QPainter &painter) const override;
};
