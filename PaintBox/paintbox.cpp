#include "paintbox.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <QEvent>

#include <QPainter>
#include <QPixmap>

#include "Chunk/chunk.h"
#include "Shape/shape.h"
#include <Shape/line.h>

PaintBox::PaintBox(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
  setFocusPolicy(Qt::StrongFocus);
  setAttribute(Qt::WA_Hover, true);
}

PaintBox::~PaintBox() {}


void PaintBox::paintObj(Shape *obj) {
  QPainter painter(this);
  QBrush br(obj->getColor());
  painter.setBrush(br);
  painter.setPen(QColor(0, 0, 0, 0));

  obj->draw(painter);
}

void PaintBox::paintSelection(const Selection &selection) {
  QPainter painter(this);
  painter.setPen(Qt::blue);
  selection.draw(painter);
}

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

void PaintBox::mouseReleaseEvent(QMouseEvent *event) {
  emit mouseRelease(event);
}

void PaintBox::keyPressEvent(QKeyEvent *event) { emit keyPress(event); }

void PaintBox::resizeEvent(QResizeEvent *event) { emit resize(event); }

bool PaintBox::event(QEvent *event) {
  switch (event->type()) {
    case QEvent::HoverMove:
      emit hoverMove(static_cast<QHoverEvent *>(event));
      return true;
    case QEvent::HoverLeave:
      emit hoverLeave(static_cast<QHoverEvent *>(event));
      return true;
    default:
      break;
  }
  return QWidget::event(event);
}
