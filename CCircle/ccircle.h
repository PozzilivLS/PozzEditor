#pragma once

#include <QPoint>
#include <QColor>
#include <QRect>

class CCircle {
 public:
  CCircle(QPoint coordinates = QPoint(), int rad = 1, QColor color = Qt::red);
  ~CCircle();

  int getRad() const;
  QPoint getPos() const;
  QPoint getCentralPos() const;
  QColor getColor() const;

  QRect getBounds() const;

 private:
  const QPoint pos_;
  const int rad_ = 1;
  QColor color_;
};
