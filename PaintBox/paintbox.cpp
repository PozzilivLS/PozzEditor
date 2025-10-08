#include "paintbox.h"

#include <QPainter>
#include <QMouseEvent>

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
  /*lastPos_ = event->pos();
  CCircle *circle = new CCircle(this, 30, event->pos());
  circle->show();
  globalStorage_->addElement(circle);
  chunks_.emplace_back(new Chunk<CCircle*>());
  chunks_.back()->addElement(circle);*/
}

void PaintBox::mouseMoveEvent(QMouseEvent *event) {
  /*if ((lastPos_ - event->pos()).manhattanLength() >= epsilon_) {
    CCircle *circle = new CCircle(this, 30, event->pos());
    circle->show();
    chunks_.back()->addElement(circle);
    lastPos_ = event->pos();
  }*/
}
