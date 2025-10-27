#pragma once

#include <QPoint>
#include <QColor>
#include <QRect>
#include <QSize>

enum class ShapeType { Rect = 0, Ellipse = 1, Triangle = 2, Chunk = 3, None = 100 };

class Shape {
 public:
  Shape(QPoint coordinates = QPoint(), QSize size = QSize(),
        QColor color = Qt::red);

  virtual ~Shape();

  void moveDiff(int x, int y);
  void resizeDiff(int x, int y);

  virtual ShapeType type() const { return ShapeType::None; }

  QSize getSize() const;
  QPoint getPos() const;
  QPoint getCentralPos() const;
  QColor getColor() const;

  virtual QRect getBounds() const;

  virtual bool hasPointIn(QPoint point) const = 0;

 protected:
  QPoint pos_;
  QSize size_;
  QColor color_;
};
