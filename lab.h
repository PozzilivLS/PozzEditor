#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_lab.h"

class PaintBox;
class PaintBoxPresenter;
class Mouse;
class Hierarchy;

class Lab : public QMainWindow {
  Q_OBJECT

 public:
  Lab(QWidget *parent = nullptr);
  ~Lab();

  void setUpPaintBox();

  void colorChanged(QColor color);

 private slots:
  void brushSizeSliderValueChanged(int value);
  void cursorChoosed();
  void brushChoosed();
  void shapeChoosed();

  void changeColor();
  void arrowChoosed();

  void openFile();
  void saveFile();
 private:
  Ui::LabClass ui;

  QButtonGroup * toolsGroup_ = nullptr;

  PaintBox* paintBox_ = nullptr;
  PaintBoxPresenter* paintBoxPresenter_ = nullptr;

  Hierarchy* hierarchy_ = nullptr;

  Mouse* brush_ = nullptr;
  Mouse* cursor_ = nullptr;
  Mouse* shapeCreator_ = nullptr;
  Mouse* arrowsManager_ = nullptr;
};
