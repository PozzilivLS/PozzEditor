#include <QPainter>

#include "ccircle.h"

CCircle::CCircle(QWidget *parent, int rad, QPoint coordinates,
                 QColor color)
    : QWidget(parent), rad_(rad), color_(color) {
  ui.setupUi(this);

  resize(rad, rad);
  move(coordinates - QPoint(rad / 2, rad / 2));
}

CCircle::~CCircle() {}

Chunk<CCircle> *CCircle::getChunk() { return chunk_; }

void CCircle::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QBrush br(color_);
  painter.setBrush(br);
  painter.setPen(color_);
  painter.drawEllipse(rect());
}
