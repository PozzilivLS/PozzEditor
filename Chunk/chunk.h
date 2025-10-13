#pragma once
#include "./CCircle/ccircle.h"
#include "./Storage/storage.h"

class Chunk : public Storage<CCircle*> {
 public:
  ~Chunk() override;

  void addElement(CCircle* const& el) override;

  bool hasPointIn(QPoint point) const;
  bool isCircleInPoint(QPoint point) const;

  QRect getArea() const;

 private:
  int leftx_ = 0;
  int upy_ = 0;
  int rightx = 0;
  int downy_ = 0;
};
