#pragma once

#include <QObject>
#include <QPoint>
#include <QRect>
#include <vector>

#include "Observer/observer.h"
#include "Shape/shape.h"
#include "Storage/storage.h";
#include <Selection/selection.h>

class Chunk;
class Shape;

class PaintBoxModel {
  using Creator = std::function<Shape *(QPoint, QSize, QColor)>;

 public:
  PaintBoxModel();
  ~PaintBoxModel();

  void addObserver(PaintUpdatable *observer);
  void removeObserver(PaintUpdatable *observer);
  void notifyAllObservers();

  Shape *addObj(std::string type, QPoint pos = QPoint(),
                QSize size = QSize(0, 0));
  Shape *createCircleInChunk(Chunk *chunk, QPoint pos);

  void resizeObj(Shape *shape, QSize diff);
  void moveObj(Shape *shape, QPoint diff);

  bool selectObj(QPoint pos);
  void resetSelection();
  void deleteSelections();

  void groupSelected();
  void ungroupSelected();

  const Storage<Shape *> &getObjects() const;
  const Selection &getAllSelections() const;

  bool tryChangeColorForSelected(QColor color);
  void moveSelections(int xDiff, int yDiff);
  void resizeSelections(int xDiff, int yDiff);

  Selection::MousePosState checkSelectionBounds(QPoint pos);

  void calculateEdges(QSize size);
  bool isInWindow(QRect rect);

 private:
  void deleteChunk(Shape *chunk);

  std::vector<Shape *> chooseObjects(QPoint pos);

  std::vector<PaintUpdatable *> observers_;

  std::unordered_map<std::string, Creator> creators_;

  Storage<Shape *> objects_;
  Selection selections_;

  QRect edges_;
};
