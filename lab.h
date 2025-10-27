#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_lab.h"

class PaintBox;
class PaintBoxPresenter;
class Mouse;

class Lab : public QMainWindow {
  Q_OBJECT

 public:
  Lab(QWidget *parent = nullptr);
  ~Lab();

  void setUpPaintBox();
 
 private slots:
  void brushSizeSliderValueChanged(int value);
  void cursorChoosed();
  void brushChoosed();

 private:
  Ui::LabClass ui;

  QButtonGroup* toolsGroup_ = nullptr;

  PaintBox* paintBox_ = nullptr;
  PaintBoxPresenter* paintBoxPresenter_ = nullptr;

  Mouse* brush_ = nullptr;
  Mouse* cursor_ = nullptr;
};
