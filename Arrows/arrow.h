#pragma once
#include <QPoint>
#include <QPainter>
#include <QPolygon>

#include "Storage/storage.h"

class Shape;

class ArrowObserver;

class Arrow {
 public:
  Arrow(Shape *from);
  Arrow(const Arrow &) = delete;
  Arrow &operator=(const Arrow &) = delete;

  void setFixed(Shape *to);

  void addStorageObs(ArrowObserver *obs);

  enum class ShapeType { From = 0, To = 1 };

  void moved(int dX, int dY);
  void deleted(Shape *shape);

  Shape *from() { return from_; }
  Shape *to() { return to_; }

  void draw(QPainter &painter) const;

  bool isPointIn(QPoint point);

  const int ArrowSize = 6;

  QPoint EndPointInCreationMode;

 private:
  void notifyStorageAboutDeletion(ShapeType type);
  void notifyStorageAboutMove(int dx, int dy);

  bool isPointInLine(QPoint point);
  bool isPointInArrow(QPoint point);

  QPolygonF createArrowHead() const;

  Shape *from_ = nullptr;
  Shape *to_ = nullptr;

  Storage<ArrowObserver *> observers_;

  bool isFixed_ = false;
};

class ArrowObserver {
 public:
  virtual void provideArrowDeletion(Arrow *arrow, Arrow::ShapeType type) = 0;
  virtual void provideArrowMove(Arrow *arrow, int dx, int dy) = 0;
};