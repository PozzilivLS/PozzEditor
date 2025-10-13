#include "paintBoxModel.h"

PaintBoxModel::PaintBoxModel() {}

PaintBoxModel::~PaintBoxModel() {
  for (auto& chunk : chunks_) {
    delete chunk;
  }
}

void PaintBoxModel::addCircleInBox(CCircle* object) {
  globalStorage_.addElement(object);
  chunks_.back()->addElement(object);
}

void PaintBoxModel::addChunk() { chunks_.emplace_back(new Chunk()); }

void PaintBoxModel::addSelection(Chunk* selection) {
  selections_.addElement(selection);
}

void PaintBoxModel::removeSelection(Chunk* selection) {
  selections_.removeElement(selection);
}

bool PaintBoxModel::hasSelection(Chunk* selection) { return selections_.hasElement(selection); }

void PaintBoxModel::clearAllSelections() { selections_.clear(); }

void PaintBoxModel::deleteChunk(Chunk* chunk) {
  for (const auto& obj : *chunk) {
    globalStorage_.removeElement(obj);
  }
  auto iter = std::find(chunks_.begin(), chunks_.end(), chunk);
  chunks_.erase(iter);
  delete chunk;
}

const Storage<CCircle*>& PaintBoxModel::getAllObj() const {
  return globalStorage_;
}

const Storage<Chunk*>& PaintBoxModel::getAllSelections() const {
  return selections_;
}

const std::vector<Chunk*>& PaintBoxModel::getChunks() const { return chunks_; }
