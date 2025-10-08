#pragma once
#include <vector>
#include <CCircle/ccircle.h>
#include <PaintBox/paintbox.h>

class PaintBoxModel {
 public:
  PaintBoxModel();

 private:
  QPoint lastPos_;
  int epsilon_ = 5;

  std::vector<Chunk<CCircle *>> chunks_;
  Storage<CCircle *> globalStorage_;
};
