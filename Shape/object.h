#pragma once

#include <QPoint>
#include <QColor>
#include <QRect>
#include <QSize>

class Object {
 public:
  virtual ~Object();

  void moveDiff(int x, int y);
  void resizeDiff(int x, int y);

  QSize getSize() const;
  QPoint getPos() const;
  QPoint getCentralPos() const;

  virtual QRect getBounds() const;

  virtual bool hasPointIn(QPoint point) const = 0;

 protected:
  QPoint pos_;
  QSize size_;
};
