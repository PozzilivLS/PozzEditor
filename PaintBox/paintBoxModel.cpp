#include "paintBoxModel.h"

#include <Shape/group.h>

#include <QDebug>

#include "Chunk/chunk.h"
#include "ObjectFactory/objectFactory.h"
#include "Shape/ellipse.h"
#include "Shape/line.h"
#include "Shape/rect.h"
#include "Shape/triangle.h"
#include "User/user.h"
#include "Arrows/arrow.h"

PaintBoxModel::PaintBoxModel() {}

PaintBoxModel::~PaintBoxModel() {
  for (auto &object : objects_) {
    delete object;
  }
  for (auto &object : arrows_) {
    delete object;
  }
}

void PaintBoxModel::chooseObjs(Storage<Shape *> &shapes) {
  selections_.clear();

  for (auto &shape : shapes) {
    selections_.addElement(shape);
  }

  notifyAllPaintObservers();
}

void PaintBoxModel::updateObjs(Storage<Shape *> &shapes) {}

void PaintBoxModel::addElementsObserver(ElementsObserver *o) {
  elementsObservers_.emplace_back(o);
}

void PaintBoxModel::notifyAllElementsObserversOnChoose() {
  for (auto &observer : elementsObservers_) {
    observer->chooseObjs(selections_);
  }
}

void PaintBoxModel::notifyAllElementsObserversOnUpdate() {
  for (auto &observer : elementsObservers_) {
    observer->updateObjs(objects_);
  }
}

void PaintBoxModel::provideArrowDeletion(Arrow *arrow, Arrow::ShapeType type) {
  if (type == Arrow::ShapeType::To && arrow->to()->type() == "Group") {
    Storage<Shape *> grShapes = static_cast<Group *>(arrow->to())->getAllObj();
    for (auto &shape : grShapes) {
      Arrow *newArrow = new Arrow(arrow->from());
      newArrow->setFixed(shape);
      newArrow->addStorageObs(this);

      arrows_.addElement(newArrow);
    }
  }
  deleteArrow(arrow);
}

void PaintBoxModel::provideArrowMove(Shape *shape, int dx, int dy) {
  QPoint posTo(shape->getPos().x() + dx, shape->getPos().y() + dy);
  QRect newObjPos(posTo, shape->getSize());

  if (isInWindow(newObjPos).isNull()) {
    shape->move(posTo.x(), posTo.y());
  }
}

void PaintBoxModel::addPaintObserver(PaintUpdatable *observer) {
  paintObservers_.emplace_back(observer);
}

void PaintBoxModel::removePaintObserver(PaintUpdatable *observer) {
  paintObservers_.erase(
      std::remove(paintObservers_.begin(), paintObservers_.end(), observer),
      paintObservers_.end());
}

void PaintBoxModel::notifyAllPaintObservers() {
  for (auto &obs : paintObservers_) {
    obs->updateZone();
  }
}

Shape *PaintBoxModel::addObj(std::string type, QPoint pos, QSize size) {
  Shape *shape = ObjectFactory::getInstance()->createObj(type);

  if (!shape) {
    return nullptr;
  }

  shape->move(pos.x(), pos.y());
  shape->resize(size.width(), size.height());
  shape->changeColor(User::getInstance()->Color);

  objects_.addElement(shape);

  notifyAllPaintObservers();
  notifyAllElementsObserversOnUpdate();

  return shape;
}

bool PaintBoxModel::selectObj(QPoint pos) {
  Shape *choosedObject = chooseTopObject(pos);

  if (!choosedObject) {
    return false;
  }

  if (!selections_.hasElement(choosedObject)) {
    selections_.addElement(choosedObject);

    objects_.removeElement(choosedObject);
    objects_.addElement(choosedObject);
  } else {
    selections_.removeElement(choosedObject);
  }

  notifyAllPaintObservers();
  notifyAllElementsObserversOnChoose();
  return true;
}

Shape *PaintBoxModel::chooseTopObject(QPoint pos) {
  for (int i = objects_.size() - 1; i >= 0; --i) {
    if (objects_[i]->hasPointIn(pos)) {
      return objects_[i];
    }
  }

  return nullptr;
}

void PaintBoxModel::resetSelection() {
  selections_.clear();

  notifyAllPaintObservers();
  notifyAllElementsObserversOnChoose();
}

void PaintBoxModel::deleteSelections() {
  for (const auto &chunk : selections_) {
    deleteChunk(chunk);
  }

  selections_.clear();
  notifyAllPaintObservers();
  notifyAllElementsObserversOnUpdate();
}

bool PaintBoxModel::selectArrow(QPoint pos) {
  for (int i = arrows_.size() - 1; i >= 0; --i) {
    if (arrows_[i]->isPointIn(pos)) {
      if (selectedArrow_ == arrows_[i]) {
        selectedArrow_ = nullptr;
      } else {
        selectedArrow_ = arrows_[i];
      }

      notifyAllPaintObservers();
      return true;
    }
  }

  selectedArrow_ = nullptr;
  notifyAllPaintObservers();
  return false;
}

Arrow *PaintBoxModel::createArrow(Shape *from) {
  Arrow *newArrow = new Arrow(from);
  newArrow->addStorageObs(this);

  arrows_.addElement(newArrow);

  return newArrow;
}

void PaintBoxModel::deleteArrow(Arrow *arrow) {
  if (arrow->to()) arrow->to()->removeToArrow(arrow);
  if (arrow->from()) arrow->from()->removeFromArrow(arrow);

  arrows_.removeElement(arrow);
  if (arrow == selectedArrow_) {
    selectedArrow_ = nullptr;
  }
  // delete arrow;

  notifyAllPaintObservers();
}

void PaintBoxModel::moveArrowEnd(Arrow *arrow, QPoint end) {
  arrow->EndPointInCreationMode = end;

  notifyAllPaintObservers();
}

bool PaintBoxModel::tryToFixArrow(Arrow *arrow, Shape *to) {
  if (arrow->from() == to) {
    return false;
  }

  for (auto &obj : arrows_) {
    if (obj->from() == arrow->from() && obj->to() == to) {
      return false;
    }
  }

  arrow->setFixed(to);
  notifyAllPaintObservers();
  return true;
}

const Storage<Arrow *> &PaintBoxModel::getArrows() const { return arrows_; }

Arrow *PaintBoxModel::getSelectedArrow() const { return selectedArrow_; }

void PaintBoxModel::groupSelected() {
  Storage<Shape *> storage;
  Storage<Arrow *> arrowsToDel;

  for (auto &obj : selections_) {
    storage.addElement(obj);
    objects_.removeElement(obj);

    for (auto &arrow : arrows_) {
      if (arrow->from() == obj || arrow->to() == obj) {
        arrowsToDel.addElement(arrow);
      }
    }
  }

  for (auto &arrow : arrowsToDel) {
    deleteArrow(arrow);
  }

  Group *group = new Group(std::move(storage));
  selections_.clear();

  selections_.addElement(group);
  objects_.addElement(group);

  notifyAllPaintObservers();
  notifyAllElementsObserversOnUpdate();
  notifyAllElementsObserversOnChoose();
}

void PaintBoxModel::ungroupSelected() {
  if (selections_.size() != 1 || !dynamic_cast<Group *>(selections_[0])) {
    return;
  }

  Group *g = dynamic_cast<Group *>(selections_[0]);

  Storage<Shape *> &objects = g->getAllObj();

  objects_.removeElement(g);
  selections_.removeElement(g);

  for (auto &obj : objects) {
    objects_.addElement(obj);
    selections_.addElement(obj);
  }

  delete g;

  notifyAllPaintObservers();
  notifyAllElementsObserversOnUpdate();
  notifyAllElementsObserversOnChoose();
}

Shape *PaintBoxModel::createCircleInChunk(Chunk *chunk, QPoint pos) {
  int rad = User::getInstance()->BrushSize;
  QPoint circlePos(pos.x() - rad / 2, pos.y() - rad / 2);
  Ellipse *circle = new Ellipse(circlePos, QSize(rad, rad),
                                User::getInstance()->Color);  // HARD ELLIPSE
  chunk->addElement(circle);

  notifyAllPaintObservers();

  return circle;
}

void PaintBoxModel::resizeObj(Shape *shape, QSize diff) {
  shape->resize(shape->getSize().width() + diff.width(),
                shape->getSize().height() + diff.height());
  notifyAllPaintObservers();
}

void PaintBoxModel::moveObj(Shape *shape, QPoint diff) {
  shape->move(shape->getPos().x() + diff.x(), shape->getPos().y() + diff.y());
  notifyAllPaintObservers();
}

void PaintBoxModel::deleteChunk(Shape *chunk) {  // TODO: if chunk in selection
  objects_.removeElement(chunk);
  delete chunk;
}

const Selection &PaintBoxModel::getAllSelections() const { return selections_; }

bool PaintBoxModel::tryChangeColorForSelected(QColor color) {
  if (selections_.size() == 0) {
    return false;
  }

  for (const auto &obj : selections_) {
    obj->changeColor(color);
  }
  return true;
}

void PaintBoxModel::moveSelections(int xDiff, int yDiff) {
  selections_.moveSelections(xDiff, yDiff);
  notifyAllPaintObservers();
}

void PaintBoxModel::resizeSelections(int xDiff, int yDiff) {
  selections_.resizeSelections(xDiff, yDiff);
  notifyAllPaintObservers();
}

Selection::MousePosState PaintBoxModel::checkSelectionBounds(QPoint pos) {
  return selections_.checkMousePos(pos);
}

void PaintBoxModel::calculateEdges(QSize size) {
  borders_ = QRect(QPoint(0, 0), size);
}

QPoint PaintBoxModel::isInWindow(QRect rect) {
  if (borders_.contains(rect)) {
    return QPoint();
  }

  rect = rect.normalized();

  int horOut = 0;
  if (borders_.left() - rect.left() > 0) {
    horOut = borders_.left() - rect.left();
  }
  if (borders_.right() - rect.right() < 0) {
    horOut = borders_.right() - rect.right();
  }

  int verOut = 0;
  if (borders_.top() - rect.top() > 0) {
    verOut = borders_.top() - rect.top();
  }
  if (borders_.bottom() - rect.bottom() < 0) {
    verOut = borders_.bottom() - rect.bottom();
  }

  return QPoint(horOut, verOut);
}

void PaintBoxModel::save(char *name) { saveLoader_.save(name, objects_); }

void PaintBoxModel::load(char *name) {
  objects_.clear();
  selections_.clear();

  saveLoader_.load(name, objects_);

  notifyAllPaintObservers();
  notifyAllElementsObserversOnUpdate();
}

const Storage<Shape *> &PaintBoxModel::getObjects() const { return objects_; }
