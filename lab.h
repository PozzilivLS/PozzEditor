#pragma once

#include <QtWidgets/QMainWindow>

#include "PaintBox/paintbox.h"
#include <paintBoxPresenter.h>
#include "ui_lab.h"

class Lab : public QMainWindow {
  Q_OBJECT

 public:
  Lab(QWidget *parent = nullptr);
  ~Lab();

  void setUpPaintBox();
 
 private slots:
  void brushSizeSliderValueChanged(int value);

 private:
  PaintBox* paintBox_;
  PaintBoxPresenter* paintBoxPresenter_;
  Ui::LabClass ui;
};
