#pragma once

#include <QWidget>

#include "ui_ccircle.h"

class CCircle : public QWidget {
  Q_OBJECT

 public:
  CCircle(QWidget *parent = nullptr, int rad = 100, QPoint coordinates = QPoint(),
          QColor color = Qt::red);
  ~CCircle();

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  int rad_ = 1;
  QColor color_;

  Ui::CCircleClass ui;
};
