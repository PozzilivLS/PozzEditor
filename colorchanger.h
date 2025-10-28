#pragma once

#include <QMainWindow>

#include "ui_colorchanger.h"

class ColorChanger : public QMainWindow {
  Q_OBJECT

 public:
  ColorChanger(QWidget *parent = nullptr);
  ~ColorChanger();

  QColor getColor();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void colorChanged();

signals:
  void closed(QColor color);

 private:
  Ui::ColorChangerClass ui;

  QColor color_;
};
