#include "paintbox.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

#include "Chunk/chunk.h"
#include "Shape/shape.h"
#include <Shape/line.h>

PaintBox::PaintBox(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
  setFocusPolicy(Qt::StrongFocus);

  paintMethods_[ShapeType::Rect] = [](Shape *rect, QPainter &painter) {
    QRect r(rect->getPos(), rect->getSize());
    painter.drawRect(r);
  };
  paintMethods_[ShapeType::Ellipse] = [](Shape *ellipse,
                                         QPainter &painter) {
    QRect r(ellipse->getPos(), ellipse->getSize());
    painter.drawEllipse(r);
  };
  paintMethods_[ShapeType::Triangle] = [](Shape *triangle,
                                          QPainter &painter) {
    QPolygon poly;
    QPoint pos = triangle->getPos();
    QSize size = triangle->getSize();
    poly << QPoint(pos + QPoint(0, size.height()))
         << QPoint(pos + QPoint(size.width(), size.height()))
         << QPoint(pos + QPoint(size.width() / 2, 0));
    painter.drawPolygon(poly);
  };
  paintMethods_[ShapeType::Line] = [](Shape *line, QPainter &painter) {
    QPoint p1(line->getPos());
    QPoint p2(p1.x() + line->getSize().width(), p1.y() + line->getSize().height());

    QPen pen;
    pen.setColor(painter.brush().color());
    pen.setWidth(static_cast<Line *>(line)->getLineSize());
    painter.setPen(pen);

    painter.drawLine(p1, p2);
  };
  paintMethods_[ShapeType::Chunk] = [this](Shape *shapeChunk,
                                           QPainter &painter) {
    Chunk *chunk = static_cast<Chunk *>(shapeChunk);
    if (!chunk->isFixed()) {

      QPainter chunkPainter(&(chunk->getPixmap()));
      QBrush br(chunk->getColor());
      chunkPainter.setBrush(br);
      chunkPainter.setPen(painter.pen().color());
      for (const auto &obj : *chunk) {
        paintMethods_[obj->type()](obj, chunkPainter);
      }
    }

    painter.drawPixmap(QPoint(), chunk->getPixmap());
  };
}

PaintBox::~PaintBox() {}


void PaintBox::paintObj(Shape *obj) {
  QPainter painter(this);
  QBrush br(obj->getColor());
  painter.setBrush(br);
  painter.setPen(QColor(0, 0, 0, 0));

  paintMethods_[obj->type()](obj, painter);
}

void PaintBox::paintSelection(const QRect selection) {
  QPainter painter(this);
  painter.setPen(Qt::blue);
  painter.drawRect(selection);
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
