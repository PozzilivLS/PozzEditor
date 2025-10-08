#pragma once

#include <QWidget>

#include "ui_ccircle.h"
#include <Chunk/chunk.h>

class CCircle : public QWidget {
  Q_OBJECT

 public:
  CCircle(QWidget *parent = nullptr, int rad = 100, QPoint coordinates = QPoint(),
          QColor color = Qt::red);
  ~CCircle();

  Chunk<CCircle> *getChunk();

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  const int rad_ = 1;
  QColor color_;

  Chunk<CCircle> *chunk_;

  Ui::CCircleClass ui;
};
