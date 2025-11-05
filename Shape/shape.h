#pragma once

#include <QPoint>
#include <QColor>
#include <QRect>
#include <QSize>
#include <QPainter>

enum class ShapeType { Rect = 0, Ellipse = 1, Triangle = 2, Line = 3, Chunk = 10, None = 100 };

class Shape {
 public:
  Shape(QPoint coordinates = QPoint(), QSize size = QSize(),
        QColor color = Qt::red);

  virtual ~Shape();

  virtual void move(float x, float y);
  virtual void resize(float x, float y);

  virtual void changeColor(QColor color);

  virtual ShapeType type() const { return ShapeType::None; }

  QSize getSize() const;
  QPoint getPos() const;
  QPoint getCentralPos() const;
  QColor getColor() const;

  virtual QRect getBounds() const;

  virtual bool hasPointIn(QPoint point) const = 0;

  virtual void draw(QPainter &painter) const = 0;

 protected:
  QPointF pos_;
  QSizeF size_;
  QColor color_;
};
