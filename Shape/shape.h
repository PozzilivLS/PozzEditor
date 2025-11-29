#pragma once

#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QSize>

#include "Storage/storage.h"
#include "Arrows/arrow.h"

enum class ShapeType {
  Rect = 0,
  Ellipse = 1,
  Triangle = 2,
  Line = 3,
  Chunk = 10,
  None = 100
};

class Shape {
 public:
  Shape(QPoint coordinates = QPoint(), QSize size = QSize(),
        QColor color = Qt::red);

  virtual ~Shape();

  virtual void move(int x, int y);
  virtual void resize(int x, int y);

  virtual void changeColor(QColor color);

  virtual const char* type() const { return "None"; }
  QSize getSize() const;
  QPoint getPos() const;
  QPoint getCentralPos() const;
  QColor getColor() const;

  virtual QRect getBounds() const;

  virtual bool hasPointIn(QPoint point) const = 0;

  virtual void draw(QPainter& painter) const = 0;

  virtual void save(FILE* file);
  virtual void load(FILE* file);

  int getId();

  void addToArrow(Arrow* arrow);
  void removeToArrow(Arrow* arrow);
  void addFromArrow(Arrow* arrow);
  void removeFromArrow(Arrow* arrow);

 protected:
  void notifyFromArrowsAboutMove(int xDiff, int yDiff);
  void notifyAllArrowsAboutDelete();

  int id_ = 0;

  QPoint pos_;
  QSize size_;
  QColor color_;
 
 private:
  void generateId();

  Storage<Arrow *> fromArrows_;
  Storage<Arrow *> toArrows_;
};
