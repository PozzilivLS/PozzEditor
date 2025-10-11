#pragma once

#include <QWidget>

#include "./Chunk/chunk.h"
#include "ui_ccircle.h"

class CCircle {
 public:
  CCircle(QPoint coordinates = QPoint(), int rad = 1, QColor color = Qt::red);
  ~CCircle();

  Chunk *getChunk() const;
  int getRad() const;
  QPoint getPos() const;
  QColor getColor() const;

 private:
  const QPoint pos_;
  const int rad_ = 1;
  QColor color_;

  Chunk *chunk_;
};
