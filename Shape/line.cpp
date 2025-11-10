#include "line.h"

#include <QDebug>

#include "User/user.h"

Line::Line(QPoint coordinates, QSize size, QColor color)
    : Shape(coordinates, size, color) {
  lineSize_ = User::getInstance()->BrushSize;
}

bool Line::hasPointIn(QPoint point) const {
  QPointF ab(size_.width(), size_.height());
  QPointF ap(point - pos_);

  float t =
      (ap.x() * ab.x() + ap.y() * ab.y()) / (ab.x() * ab.x() + ab.y() * ab.y());

  float d = 0;

  if (0 <= t && t <= 1) {
    QPointF pp(pos_.x() + t * ab.x(), pos_.y() + t * ab.y());
    d = sqrt((point.x() - pp.x()) * (point.x() - pp.x()) +
             (point.y() - pp.y()) * (point.y() - pp.y()));
  } else {
    QPointF bp(point.x() - pos_.x() + size_.width(),
               point.y() - pos_.y() + size_.height());
    d = fminf(sqrt(ap.x() * ap.x() + ap.y() * ap.y()),
              sqrt(bp.x() * bp.x() + bp.y() * bp.y()));
  }

  return d <= lineSize_ / 2;
}

QRect Line::getBounds() const {
  QPointF ab(size_.width(), size_.height());
  float l =
      sqrt(size_.width() * size_.width() + size_.height() * size_.height());

  QPointF Eab(ab * lineSize_ / 2 / l);
  QPointF Nab(-Eab.y(), Eab.x());

  QPoint diff((Eab + Nab).x(), (Eab + Nab).y());
  QRect res(pos_, size_);
  //res.adjust(-diff.x(), -diff.y(), diff.x(), diff.y());

  return res;
}

void Line::draw(QPainter& painter) const {
  QPoint p1(pos_);
  QPoint p2(p1.x() + size_.width(),
            p1.y() + size_.height());

  QPen pen;
  pen.setColor(painter.brush().color());
  pen.setWidth(lineSize_);
  painter.setPen(pen);

  painter.drawLine(p1, p2);
}

int Line::getLineSize() { return lineSize_; }
