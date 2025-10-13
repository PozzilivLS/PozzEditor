#pragma once
#include <Chunk/chunk.h>

#include <vector>

#include "./CCircle/ccircle.h"

class PaintBoxModel {
 public:
  PaintBoxModel();
  ~PaintBoxModel();

  void addCircleInBox(CCircle *object);
  void addChunk();
  void addSelection(Chunk *selection);
  void removeSelection(Chunk *selection);
  bool hasSelection(Chunk *selection);
  void clearAllSelections();
  void deleteChunk(Chunk *chunk);

  const std::vector<Chunk *> &getChunks() const;
  const Storage<CCircle *> &getAllObj() const;
  const Storage<Chunk *> &getAllSelections() const;

 private:
  std::vector<Chunk *> chunks_;
  Storage<CCircle *> globalStorage_;
  Storage<Chunk *> selections_;
};
