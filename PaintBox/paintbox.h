#pragma once

#include <QWidget>

#include "ui_paintbox.h"

class QPaintEvent;
class QMouseEvent;
class QKeyEvent;
class Object;
class QPixmap;
class Chunk;

class PaintBox : public QWidget {
  Q_OBJECT

 public:
  PaintBox(QWidget *parent = nullptr);
  ~PaintBox();

  void paintObj(const Object *obj, QPixmap& pixmap);
  void paintChunk(const Chunk *chunk);
  void paintSelection(const Chunk *selection);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 signals:
  void mousePress(QMouseEvent *event);
  void mouseMove(QMouseEvent *event);
  void paint(QPaintEvent *event);
  void keyPress(QKeyEvent *event);

 private:
  Ui::PaintBoxClass ui;
};
