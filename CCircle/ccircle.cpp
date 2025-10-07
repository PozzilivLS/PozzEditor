#include <QPainter>

#include "ccircle.h"

CCircle::CCircle(QWidget *parent, int rad, QPointF coordinates,
                 QColor color)
    : QWidget(parent), rad_(rad), color_(color) {
  ui.setupUi(this);
  //qDebug() << "da";

  resize(rad, rad);
  move(QPoint(coordinates.x(), coordinates.y()));
}

CCircle::~CCircle() {}

void CCircle::paintEvent(QPaintEvent *event) {
  qDebug() << "da";
  QPainter painter(this);
  QBrush br(color_);
  painter.setBrush(br);
  painter.setPen(color_);
  painter.drawEllipse(pos(), rad_, rad_);
}
