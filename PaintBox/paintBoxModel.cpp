#include "paintBoxModel.h"

PaintBoxModel::PaintBoxModel() {}

void PaintBoxModel::addCircleInBox(CCircle* object) {
  globalStorage_.addElement(object);
  chunks_.back().addElement(object);
}

void PaintBoxModel::addChunk() { chunks_.emplace_back(Chunk()); }

const Storage<CCircle*>& PaintBoxModel::getAllObj() const {
  return globalStorage_;
}

const std::vector<Chunk>& PaintBoxModel::getChunks() const {
  return chunks_;
}
