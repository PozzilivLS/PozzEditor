#include "paintBoxPresenter.h"

#include <CCircle/ccircle.h>
#include <User/user.h>
#include <Chunk/chunk.h>

#include <QMouseEvent>
#include <QPainter>

PaintBoxPresenter::PaintBoxPresenter(QObject* parent)
    : QObject(parent), model_(new PaintBoxModel()) {}

void PaintBoxPresenter::subscribeView(PaintBox* view) {
  view_ = view;
  QObject::connect(view_, SIGNAL(mousePress(QMouseEvent*)),
                   SLOT(onMousePress(QMouseEvent*)));
  QObject::connect(view_, SIGNAL(mouseMove(QMouseEvent*)),
                   SLOT(onMouseMove(QMouseEvent*)));
  QObject::connect(view_, SIGNAL(paint(QPaintEvent*)),
                   SLOT(onPaint(QPaintEvent*)));
}

void PaintBoxPresenter::onMousePress(QMouseEvent* event) {
  if (User::getInstance()->MouseType == MouseType::Brush) {
    model_->addChunk();
    AddObj(event->pos());
  }
}

void PaintBoxPresenter::onMouseMove(QMouseEvent* event) {
  if (User::getInstance()->MouseType == MouseType::Brush &&
      !User::getInstance()->SingleDrawing) {
    if ((lastPos_ - event->pos()).manhattanLength() >= epsilon_) {
      AddObj(event->pos());
    }
  }
}

void PaintBoxPresenter::onPaint(QPaintEvent* event) {
  const Storage<CCircle*>& objects = model_->getAllObj();
  for (const auto& obj : objects) {
    PaintObj(obj);
  }
}

void PaintBoxPresenter::AddObj(QPoint pos) {
  lastPos_ = pos;
  int rad = User::getInstance()->BrushSize / 2;
  QPoint circlePos(pos.x() - rad, pos.y() - rad);
  CCircle* circle = new CCircle(circlePos, rad);
  model_->addCircleInBox(circle);

  PaintObj(circle);
}

void PaintBoxPresenter::PaintObj(const CCircle* obj) {
  QPainter painter(view_);
  QBrush br(obj->getColor());
  painter.setBrush(br);
  painter.setPen(obj->getColor());
  QRect rect(obj->getPos(), QSize(obj->getRad() * 2, obj->getRad() * 2));
  painter.drawEllipse(rect);
}

void PaintBoxPresenter::ChooseObj(QPoint pos) {
  const Chunk& choosedChunk = ChooseChunk(pos);

  if (choosedChunk.size() > 0) {
    if (choosedChunk.isCircleInPoint(pos)) {
      
    }
  }
}

const Chunk& PaintBoxPresenter::ChooseChunk(QPoint pos) {
  const std::vector<Chunk>& chunks = model_->getChunks();

  for (int i = chunks.size() - 1; i >= 0; --i) {
    if (chunks[i].hasPointIn(pos)) {
      return chunks[i];
    }
  }

  return Chunk();
}
