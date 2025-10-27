#include "paintBoxModel.h"

#include "Chunk/chunk.h"
#include "Shape/ellipse.h"
#include "Shape/rect.h"
#include "Shape/triangle.h"
#include "User/user.h"
#include <QDebug>

PaintBoxModel::PaintBoxModel() {
  creators_[ShapeType::Rect] = [](QPoint pos, QSize size, QColor color) {
    return new Rect(pos, size, color);
  };
  creators_[ShapeType::Ellipse] = [](QPoint pos, QSize size, QColor color) {
    return new Ellipse(pos, size, color);
  };
  creators_[ShapeType::Triangle] = [](QPoint pos, QSize size, QColor color) {
    return new Triangle(pos, size, color);
  };
  creators_[ShapeType::Chunk] = [](QPoint pos, QSize size, QColor color) {
    return new Chunk(); // TODO: I dont use args
  };
}

PaintBoxModel::~PaintBoxModel() {
  for (auto &object : objects_) {
    delete object;
  }
}

void PaintBoxModel::AddObserver(PaintUpdatable *observer) {
  observers_.emplace_back(observer);
}

void PaintBoxModel::RemoveObserver(PaintUpdatable *observer) {
  observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                   observers_.end());
}

void PaintBoxModel::NotifyAllObservers() {
  for (auto &obs : observers_) {
    obs->updateZone();
  }
}

Shape *PaintBoxModel::addObj(ShapeType type, QPoint pos, QSize size) {
  if (creators_.count(type) == 0) {
    return nullptr;
  }

  Shape *shape = creators_[type](pos, size, Qt::red);

  objects_.addElement(shape);

  NotifyAllObservers();

  return shape;
}

bool PaintBoxModel::selectObj(QPoint pos) {
  std::vector<Shape *> choosedChunks = chooseObjects(pos);

  if (choosedChunks.empty()) {
    return false;
  }

  const auto &chunk = choosedChunks.front();

  if (!hasSelection(chunk)) {
    addSelection(chunk);
  } else {
    removeSelection(chunk);
  }
  NotifyAllObservers();
  return true;
}

void PaintBoxModel::resetSelection() {
  clearAllSelections();
  NotifyAllObservers();
}

void PaintBoxModel::deleteSelections() {
  for (const auto &chunk : selections_) {
    deleteChunk(chunk);
  }

  clearAllSelections();
  NotifyAllObservers();
}

Shape *PaintBoxModel::createCircleInChunk(Chunk *chunk, QPoint pos) {
  int rad = User::getInstance()->BrushSize;
  QPoint circlePos(pos.x() - rad / 2, pos.y() - rad / 2);
  Ellipse *circle = new Ellipse(circlePos, QSize(rad, rad), Qt::red);
  chunk->addElement(circle);

  NotifyAllObservers();

  return circle;
}

void PaintBoxModel::addSelection(Shape *selection) {
  selections_.addElement(selection);
}

void PaintBoxModel::removeSelection(Shape *selection) {
  selections_.removeElement(selection);
}

bool PaintBoxModel::hasSelection(Shape *selection) {
  return selections_.hasElement(selection);
}

void PaintBoxModel::clearAllSelections() { selections_.clear(); }

void PaintBoxModel::deleteChunk(Shape *chunk) { // TODO: if chunk in selection
  objects_.removeElement(chunk);
  delete chunk;
}

const Storage<Shape *> &PaintBoxModel::getAllSelections() const {
  return selections_;
}

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