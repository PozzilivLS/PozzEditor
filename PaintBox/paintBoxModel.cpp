#include "paintBoxModel.h"

#include "./Shape/shape.h"
#include "Chunk/chunk.h"
#include "User/user.h"

PaintBoxModel::PaintBoxModel() {}

PaintBoxModel::~PaintBoxModel() {
  for (auto& chunk : chunks_) {
    delete chunk;
  }
}

void PaintBoxModel::AddObserver(PaintUpdatable* observer) {
  observers_.emplace_back(observer);
}

void PaintBoxModel::RemoveObserver(PaintUpdatable* observer) {
  observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                   observers_.end());
}

void PaintBoxModel::NotifyAllObservers() {
  for (auto& obs : observers_) {
    obs->updateZone();
  }
}

void PaintBoxModel::addObj(QPoint pos) {
  int rad = User::getInstance()->BrushSize / 2;
  QPoint circlePos(pos.x() - rad, pos.y() - rad);
  Object* circle = new Object(circlePos, QSize(rad * 2, rad * 2));
  addShapeInLastBox(circle);

  NotifyAllObservers();
}

bool PaintBoxModel::chooseObj(QPoint pos) {
  std::vector<Chunk*> choosedChunks = chooseChunks(pos);

  for (const auto& chunk : choosedChunks) {
    if (chunk->isCircleInPoint(pos)) {
      if (!hasSelection(chunk)) {
        addSelection(chunk);
      } else {
        removeSelection(chunk);
      }

      NotifyAllObservers();

      return true;
    }
  }

  return false;
}

void PaintBoxModel::resetSelection() {
  clearAllSelections();
  NotifyAllObservers();
}

void PaintBoxModel::deleteSelections() {
  for (const auto& chunk : selections_) {
    deleteChunk(chunk);
  }

  clearAllSelections();
  NotifyAllObservers();
}

void PaintBoxModel::addShapeInLastBox(Object* object) {
  chunks_.last()->addElement(object);
}

void PaintBoxModel::createChunk() { chunks_.addElement(new Chunk()); }

void PaintBoxModel::addSelection(Chunk* selection) {
  selections_.addElement(selection);
}

void PaintBoxModel::removeSelection(Chunk* selection) {
  selections_.removeElement(selection);
}

bool PaintBoxModel::hasSelection(Chunk* selection) {
  return selections_.hasElement(selection);
}

void PaintBoxModel::clearAllSelections() { selections_.clear(); }

void PaintBoxModel::deleteChunk(Chunk* chunk) {
  chunks_.removeElement(chunk);
  delete chunk;
}

const Storage<Chunk*>& PaintBoxModel::getAllSelections() const {
  return selections_;
}

const Storage<Chunk*>& PaintBoxModel::getChunks() const { return chunks_; }


std::vector<Chunk*> PaintBoxModel::chooseChunks(QPoint pos) {
  std::vector<Chunk*> res;

  for (int i = chunks_.size() - 1; i >= 0; --i) {
    if (chunks_[i]->hasPointIn(pos)) {
      res.emplace_back(chunks_[i]);
    }
  }

  return res;
}