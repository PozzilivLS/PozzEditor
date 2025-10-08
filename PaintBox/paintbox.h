#pragma once

#include <QWidget>

#include "../CCircle/ccircle.h"
#include "../Chunk/chunk.h"
#include "../Storage/storage.h"
#include "ui_paintbox.h"

class PaintBox : public QWidget {
  Q_OBJECT

 public:
  PaintBox(QWidget *parent = nullptr);
  ~PaintBox();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  Ui::PaintBoxClass ui;
};
