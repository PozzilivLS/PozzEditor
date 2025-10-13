#pragma once

#include <QWidget>

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
  void keyPressEvent(QKeyEvent *event) override;

 signals:
  void mousePress(QMouseEvent *event);
  void mouseMove(QMouseEvent *event);
  void paint(QPaintEvent *event);
  void keyPress(QKeyEvent *event);

 private:
  Ui::PaintBoxClass ui;
};
