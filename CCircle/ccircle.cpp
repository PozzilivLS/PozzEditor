#include "ccircle.h"

#include <QPainter>

CCircle::CCircle(QPoint coordinates, int rad, QColor color)
    : pos_(coordinates), rad_(rad), color_(color) {}

CCircle::~CCircle() {}

int CCircle::getRad() const { return rad_; }

QPoint CCircle::getPos() const { return pos_; }

QPoint CCircle::getCentralPos() const { return pos_ + QPoint(rad_, rad_); }

QColor CCircle::getColor() const { return color_; }

QRect CCircle::getBounds() const {
  return QRect(pos_, QSize(rad_ * 2, rad_ * 2));
}
