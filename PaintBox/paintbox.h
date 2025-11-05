#pragma once

#include <QWidget>

#include "ui_paintbox.h"
#include "Shape/shape.h"
#include <Selection/selection.h>

class QPaintEvent;
class QMouseEvent;
class QResizeEvent;
class QEvent;
class QKeyEvent;
class Shape;
class QPixmap;

class PaintBox : public QWidget {
  Q_OBJECT

 public:
  PaintBox(QWidget *parent = nullptr);
  ~PaintBox();

  void paintObj(Shape *obj);
  void paintSelection(const Selection &selection);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

 protected:
  bool event(QEvent *event) override;

 signals:
  void mousePress(QMouseEvent *event);
  void mouseMove(QMouseEvent *event);
  void mouseRelease(QMouseEvent *event);
  void paint(QPaintEvent *event);
  void keyPress(QKeyEvent *event);
  void hoverMove(QHoverEvent *event);
  void hoverLeave(QHoverEvent *event);
  void resize(QResizeEvent *event);

 private:
  Ui::PaintBoxClass ui;
};
