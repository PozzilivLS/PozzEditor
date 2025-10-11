#pragma once
#include <vector>

#include "./CCircle/ccircle.h"

class PaintBoxModel {
 public:
  PaintBoxModel();

  void addCircleInBox(CCircle *object);
  void addChunk();

  const std::vector<Chunk> &getChunks() const;
  const Storage<CCircle *> &getAllObj() const;
 private:
  std::vector<Chunk> chunks_;
  Storage<CCircle *> globalStorage_;
};
