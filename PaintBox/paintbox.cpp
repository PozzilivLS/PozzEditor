#include "paintbox.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

#include "Chunk/chunk.h"
#include "Shape/shape.h"

PaintBox::PaintBox(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
  setFocusPolicy(Qt::StrongFocus);
}

PaintBox::~PaintBox() {}

void PaintBox::paintObj(const Object *obj, QPixmap &pixmap) {
  QPainter painter(&pixmap);
  QBrush br(obj->getColor());
  painter.setBrush(br);
  painter.setPen(obj->getColor());
  QRect rect(obj->getPos(), obj->getSize());
  painter.drawEllipse(rect);
}

void PaintBox::paintChunk(const Chunk *chunk) {
  QPainter painter(this);
  painter.drawPixmap(QPoint(), chunk->getPixmap());
}

void PaintBox::paintSelection(const Chunk *selection) {
  QPainter painter(this);
  painter.setPen(Qt::blue);
  QRect r(selection->getPos(),
          selection->getPixmap().size() -
              QSize(selection->getPos().x(), selection->getPos().y()));
  painter.drawRect(r);
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

void PaintBox::keyPressEvent(QKeyEvent *event) { emit keyPress(event); }
