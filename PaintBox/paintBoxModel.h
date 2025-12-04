#pragma once

#include <QObject>
#include <QPoint>
#include <QRect>
#include <vector>

#include "Observer/observer.h"
#include "SaveLoader/saveLoader.h"
#include "Selection/elementsObserver.h"
#include "Selection/selection.h"

class Chunk;
class Shape;
class Arrow;

class PaintBoxModel : public ElementsObserver, public ArrowObserver {
 public:
  PaintBoxModel();
  ~PaintBoxModel();

  void chooseObjs(Storage<Shape *> &shapes) override;
  void updateObjs(Storage<Shape *> &shapes) override;
  void addElementsObserver(ElementsObserver *o);
  void notifyAllElementsObserversOnChoose();
  void notifyAllElementsObserversOnUpdate();

  void provideArrowDeletion(Arrow *arrow, Arrow::ShapeType type) override;
  void provideArrowMove(Arrow *arrow, int dx, int dy) override;

  void addPaintObserver(PaintUpdatable *observer);
  void removePaintObserver(PaintUpdatable *observer);
  void notifyAllPaintObservers();

  Shape *addObj(std::string type, QPoint pos = QPoint(),
                QSize size = QSize(0, 0));
  Shape *createCircleInChunk(Chunk *chunk, QPoint pos);

  void resizeObj(Shape *shape, QSize diff);
  void moveObj(Shape *shape, QPoint diff);

  bool selectObj(QPoint pos);
  Shape *chooseTopObject(QPoint pos);

  void resetSelection();
  void deleteSelections();

  bool selectArrow(QPoint pos);
  Arrow *createArrow(Shape *from);
  void deleteArrow(Arrow *arrow);
  void moveArrowEnd(Arrow *arrow, QPoint end);
  bool tryToFixArrow(Arrow *arrow, Shape *to);

  const Storage<Arrow *> &getArrows() const;
  Arrow * getSelectedArrow() const;

  void groupSelected();
  void ungroupSelected();

  const Storage<Shape *> &getObjects() const;
  const Selection &getAllSelections() const;

  bool tryChangeColorForSelected(QColor color);
  void moveSelections(int xDiff, int yDiff);
  void resizeSelections(int xDiff, int yDiff);

  Selection::MousePosState checkSelectionBounds(QPoint pos);

  void calculateEdges(QSize size);
  QPoint isInWindow(QRect rect);

  void save(char *name);
  void load(char *name);

 private:
  void deleteChunk(Shape *chunk);

  std::vector<PaintUpdatable *> paintObservers_;
  std::vector<ElementsObserver *> elementsObservers_;

  SaveLoader saveLoader_;

  Storage<Shape *> objects_;
  Selection selections_;
  
  Storage<Arrow *> arrows_;
  Storage<Shape *> movedShapes_;
  Storage<Arrow *> movedArrows_;
  Arrow *selectedArrow_;

  QRect borders_;
};
