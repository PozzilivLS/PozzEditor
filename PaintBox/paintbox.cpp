#include "paintbox.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

PaintBox::PaintBox(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
  setFocusPolicy(Qt::StrongFocus);
}

PaintBox::~PaintBox() {}

void PaintBox::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QBrush br(Qt::darkGray, Qt::SolidPattern);
  painter.setBrush(br);
  painter.setPen(Qt::darkGray);
  painter.drawRect(rect());

  emit paint(event);
}

void PaintBox::mousePressEvent(QMouseEvent *event) { emit mousePress(event); }

void PaintBox::mouseMoveEvent(QMouseEvent *event) { emit mouseMove(event); }

void PaintBox::keyPressEvent(QKeyEvent *event) { emit keyPress(event); }
