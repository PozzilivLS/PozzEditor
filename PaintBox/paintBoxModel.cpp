#include "paintBoxModel.h"

PaintBoxModel::PaintBoxModel() {}

void PaintBoxModel::addCircleInBox(CCircle* object) {
  globalStorage_.addElement(object);
  chunks_.back().addElement(object);
}

void PaintBoxModel::addChunk() { chunks_.emplace_back(Chunk<CCircle*>()); }
