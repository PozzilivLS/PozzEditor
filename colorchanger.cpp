#include "colorchanger.h"

#include <QDebug>
#include <QPalette>

ColorChanger::ColorChanger(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  connect(ui.redSlider, SIGNAL(valueChanged(int)), SLOT(colorChanged()));
  connect(ui.greenSlider, SIGNAL(valueChanged(int)), SLOT(colorChanged()));
  connect(ui.blueSlider, SIGNAL(valueChanged(int)), SLOT(colorChanged()));

  connect(ui.okButton, SIGNAL(clicked()), SLOT(close()));

  colorChanged();
}

ColorChanger::~ColorChanger() {}

QColor ColorChanger::getColor() { return color_; }

void ColorChanger::closeEvent(QCloseEvent *event) { emit closed(color_); }

void ColorChanger::colorChanged() {
  QPalette palette;
  color_ = QColor(ui.redSlider->value(), ui.greenSlider->value(),
                  ui.blueSlider->value());
  palette.setColor(QPalette::Window, color_);
  ui.colorPresenter->setPalette(palette);
}