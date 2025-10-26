#pragma once

#include "object.h"

class Shape : public Object {
 public:
  Shape() = delete;
  Shape(QPoint coordinates = QPoint(), QSize size = QSize(),
        QColor color = Qt::red);

  virtual ~Shape() {};

  QColor getColor() const;

 protected:
  QColor color_;
};
