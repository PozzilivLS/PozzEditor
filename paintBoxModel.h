#pragma once

#include <QObject>
#include <QPoint>
#include <QRect>
#include <vector>

#include "Observer/observer.h"
#include "Shape/shape.h"
#include "Storage/storage.h";

class Chunk;
class Shape;

class PaintBoxModel {
  using Creator = std::function<Shape *(QPoint, QSize, QColor)>;

 public:
  PaintBoxModel();
  ~PaintBoxModel();

  void AddObserver(PaintUpdatable *observer);
  void RemoveObserver(PaintUpdatable *observer);
  void NotifyAllObservers();

  Shape *addObj(ShapeType type, QPoint pos = QPoint(), QSize size = QSize(0, 0));
  Shape *createCircleInChunk(Chunk *chunk, QPoint pos);

  void resizeObj(Shape *shape, QSize diff);
  void moveObj(Shape *shape, QPoint diff);

  bool selectObj(QPoint pos);
  void resetSelection();
  void deleteSelections();

  const Storage<Shape *> &getObjects() const;
  const Storage<Shape *> &getAllSelections() const;

  QRect getSelectedArea() const;
  bool tryChangeColorForSelected(QColor color);
  void moveSelections(int xDiff, int yDiff);

 private:
  void addSelection(Shape *selection);
  void removeSelection(Shape *selection);
  bool hasSelection(Shape *selection);
  void deleteChunk(Shape *chunk);
  void clearAllSelections();

  std::vector<Shape *> chooseObjects(QPoint pos);

  std::vector<PaintUpdatable *> observers_;

  std::unordered_map<ShapeType, Creator> creators_;

  Storage<Shape *> objects_;
  Storage<Shape *> selections_;
};
