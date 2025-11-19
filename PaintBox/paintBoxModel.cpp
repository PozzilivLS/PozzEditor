#include "paintBoxModel.h"

#include <QDebug>

#include "Chunk/chunk.h"
#include "Shape/ellipse.h"
#include "Shape/line.h"
#include "Shape/rect.h"
#include "Shape/triangle.h"
#include "User/user.h"
#include <Shape/group.h>

PaintBoxModel::PaintBoxModel() {
  creators_["Rect"] = [](QPoint pos, QSize size, QColor color) {
    return new Rect(pos, size, color);
  };
  creators_["Ellipse"] = [](QPoint pos, QSize size, QColor color) {
    return new Ellipse(pos, size, color);
  };
  creators_["Triangle"] = [](QPoint pos, QSize size, QColor color) {
    return new Triangle(pos, size, color);
  };
  creators_["Line"] = [](QPoint pos, QSize size, QColor color) {
    return new Line(pos, size, color);
  };
  creators_["Chunk"] = [](QPoint pos, QSize size, QColor color) {
    return new Chunk(color);  // TODO: I dont use args
  };
}

PaintBoxModel::~PaintBoxModel() {
  for (auto &object : objects_) {
    delete object;
  }
}

void PaintBoxModel::addObserver(PaintUpdatable *observer) {
  observers_.emplace_back(observer);
}

void PaintBoxModel::removeObserver(PaintUpdatable *observer) {
  observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                   observers_.end());
}

void PaintBoxModel::notifyAllObservers() {
  for (auto &obs : observers_) {
    obs->updateZone();
  }
}

Shape *PaintBoxModel::addObj(std::string type, QPoint pos, QSize size) {
  if (creators_.count(type) == 0) {
    return nullptr;
  }

  Shape *shape = creators_[type](pos, size, User::getInstance()->Color);

  objects_.addElement(shape);

  notifyAllObservers();

  return shape;
}

bool PaintBoxModel::selectObj(QPoint pos) {
  std::vector<Shape *> choosedObjects = chooseObjects(pos);

  if (choosedObjects.empty()) {
    return false;
  }

  const auto &obj = choosedObjects.front();

  if (!selections_.hasElement(obj)) {
    selections_.addElement(obj);

    objects_.removeElement(obj);
    objects_.addElement(obj);
  } else {
    selections_.removeElement(obj);
  }

  notifyAllObservers();
  return true;
}

void PaintBoxModel::resetSelection() {
  selections_.clear();

  notifyAllObservers();
}

void PaintBoxModel::deleteSelections() {
  for (const auto &chunk : selections_) {
    deleteChunk(chunk);
  }

  selections_.clear();
  notifyAllObservers();
}

void PaintBoxModel::groupSelected() {
  Storage<Shape *> storage;

  for (auto &obj : selections_) {
    storage.addElement(obj);
    objects_.removeElement(obj);
  }

  Group *group = new Group(std::move(storage));
  selections_.clear();

  selections_.addElement(group);
  objects_.addElement(group);

  notifyAllObservers();
}

void PaintBoxModel::ungroupSelected() {
  if (selections_.size() != 1 || !dynamic_cast<Group *>(selections_[0])) {
    return;
  }

  Group *g = dynamic_cast<Group *>(selections_[0]);

  Storage<Shape *> &objects = g->getAllObjToUngroup();

  objects_.removeElement(g);
  selections_.removeElement(g);

  for (auto &obj : objects) {
    objects_.addElement(obj);
    selections_.addElement(obj);
  }

  objects.clear();
  delete g;

  notifyAllObservers();
}

Shape *PaintBoxModel::createCircleInChunk(Chunk *chunk, QPoint pos) {
  int rad = User::getInstance()->BrushSize;
  QPoint circlePos(pos.x() - rad / 2, pos.y() - rad / 2);
  Ellipse *circle =
      new Ellipse(circlePos, QSize(rad, rad), User::getInstance()->Color);
  chunk->addElement(circle);

  notifyAllObservers();

  return circle;
}

void PaintBoxModel::resizeObj(Shape *shape, QSize diff) {
  shape->resize(shape->getSize().width() + diff.width(),
                shape->getSize().height() + diff.height());
  notifyAllObservers();
}

void PaintBoxModel::moveObj(Shape *shape, QPoint diff) {
  shape->move(shape->getPos().x() + diff.x(), shape->getPos().y() + diff.y());
  notifyAllObservers();
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
  notifyAllObservers();
}

void PaintBoxModel::resizeSelections(int xDiff, int yDiff) {
  selections_.resizeSelections(xDiff, yDiff);
  notifyAllObservers();
}

Selection::MousePosState PaintBoxModel::checkSelectionBounds(QPoint pos) {
  return selections_.checkMousePos(pos);
}

void PaintBoxModel::calculateEdges(QSize size) {
  edges_ = QRect(QPoint(0, 0), size);
}

bool PaintBoxModel::isInWindow(QRect rect) { return edges_.contains(rect); }

const Storage<Shape *> &PaintBoxModel::getObjects() const { return objects_; }

std::vector<Shape *> PaintBoxModel::chooseObjects(QPoint pos) {
  std::vector<Shape *> res;

  for (int i = objects_.size() - 1; i >= 0; --i) {
    if (objects_[i]->hasPointIn(pos)) {
      res.emplace_back(objects_[i]);
    }
  }

  return res;
}