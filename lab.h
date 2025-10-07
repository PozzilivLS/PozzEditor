#pragma once

#include <QtWidgets/QMainWindow>

#include "PaintBox/paintbox.h"
#include "ui_lab.h"

class Lab : public QMainWindow {
  Q_OBJECT

 public:
  Lab(QWidget *parent = nullptr);
  ~Lab();

 private:
  PaintBox* paintBox_;
  Ui::LabClass ui;
};
