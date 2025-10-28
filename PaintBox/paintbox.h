#pragma once

#include <QWidget>

#include "ui_paintbox.h"
#include "Shape/shape.h"

class QPaintEvent;
class QMouseEvent;
class QKeyEvent;
class Shape;
class QPixmap;
class Chunk;

class PaintBox : public QWidget {
  using PaintMethod = std::function<void(Shape *, QPainter &)>;
  Q_OBJECT

 public:
  PaintBox(QWidget *parent = nullptr);
  ~PaintBox();

  void paintObj(Shape *obj);
  void paintSelection(const QRect selection);

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
  std::unordered_map<ShapeType, PaintMethod> paintMethods_;

  Ui::PaintBoxClass ui;
};
