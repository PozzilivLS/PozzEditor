#include "paintbox.h"

#include <QPainter>
#include <QMouseEvent>
#include "CCircle/ccircle.h"

PaintBox::PaintBox(QWidget *parent) : QWidget(parent) { ui.setupUi(this); }

PaintBox::~PaintBox() {}

void PaintBox::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QBrush br(Qt::darkGray, Qt::SolidPattern);
  //painter.setBrush(br);
  painter.setPen(Qt::darkGray);
  QRect r(pos(), size());
  painter.drawRect(r);
}

void PaintBox::mousePressEvent(QMouseEvent *event) {
  CCircle *circle = new CCircle(this, 10, event->position());
  qDebug() << circle->size() << circle->pos();
}
