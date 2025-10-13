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
 
 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

 private slots:
  void brushSizeSliderValueChanged(int value);
  void cursorChoosed();
  void brushChoosed();
  void drawingModeChanged(Qt::CheckState state);

 private:
  PaintBox* paintBox_;
  PaintBoxPresenter* paintBoxPresenter_;
  Ui::LabClass ui;
};
