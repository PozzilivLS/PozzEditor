#include "ccircle.h"

#include <QPainter>

CCircle::CCircle(QPoint coordinates, int rad, QColor color)
    : pos_(coordinates), rad_(rad), color_(color) {}

CCircle::~CCircle() {}

Chunk *CCircle::getChunk() const { return chunk_; }

int CCircle::getRad() const { return rad_; }

QPoint CCircle::getPos() const { return pos_; }

QColor CCircle::getColor() const { return color_; }
