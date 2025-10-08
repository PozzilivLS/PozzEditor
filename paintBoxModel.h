#pragma once
#include <vector>

#include "./CCircle/ccircle.h"

class PaintBoxModel {
 public:
  PaintBoxModel();

  void addCircleInBox(CCircle *object);
  void addChunk();

 private:
  std::vector<Chunk<CCircle *>> chunks_;
  Storage<CCircle *> globalStorage_;
};
