#pragma once
#include "shape.h"
class Line : public Shape {
 public:
  Line(QPoint coordinates = QPoint(), QSize size = QSize(),
          QColor color = Qt::red);

  const char *type() const override { return "Line"; }

  bool hasPointIn(QPoint point) const override;
  QRect getBounds() const override;

  void draw(QPainter &painter) const override;

  void save(FILE *file) override;
  void load(FILE *file) override;

  int getLineSize();

 private:
  int lineSize_ = 0;
};
