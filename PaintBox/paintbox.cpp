#include "paintbox.h"

#include <QPainter>
#include <QMouseEvent>
#include "CCircle/ccircle.h"

PaintBox::PaintBox(QWidget *parent) : QWidget(parent) { ui.setupUi(this); }

PaintBox::~PaintBox() {}

void PaintBox::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QBrush br(Qt::darkGray, Qt::SolidPattern);
  painter.setBrush(br);
  painter.setPen(Qt::darkGray);
  painter.drawRect(rect());
}

void PaintBox::mousePressEvent(QMouseEvent *event) {
  lastPos = event->pos();
  CCircle *circle = new CCircle(this, 30, event->pos());
  circle->show();
}

void PaintBox::mouseMoveEvent(QMouseEvent *event) {
  if ((lastPos - event->pos()).manhattanLength() >= epsilon) {
    CCircle *circle = new CCircle(this, 30, event->pos());
    circle->show();
    lastPos = event->pos();
  }
}
