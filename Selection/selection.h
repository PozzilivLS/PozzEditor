#pragma once
#include <QPainter>
#include <QRect>
#include <QWidget>

#include "Storage/storage.h"

class Shape;
class QEvent;

class Selection : public Storage<Shape *> {
  enum class ResizePositions {
    LeftUp,
    Up,
    RightUp,
    Right,
    RightDown,
    Down,
    LeftDown,
    Left,
    None
  };

 public:
  enum class MousePosState {
    BCorner = 0,
    FCorner = 1,
    HorEdge = 2,
    VerEdge = 3,
    None = 4
  };

  void addElement(Shape * const& el) override;
  void removeElement(Shape * const& el) override;
  void removeElementByIndex(const int index) override;
  void clear() override;

  void draw(QPainter& painter) const;
  QRect getArea() const;

  bool hasObjectInPoint(QPoint point) const;

  MousePosState checkMousePos(QPoint pos);

  void moveSelections(int diffX, int diffY);
  void resizeSelections(int diffX, int diffY);

 private:
  void updateRelativeInfo();

  QRect abstractLastRect_;
  ResizePositions currentResizePos_ = ResizePositions::None;
  std::unordered_map<Shape *, std::pair<QPointF, QSizeF>> relativeInfo_;
};
