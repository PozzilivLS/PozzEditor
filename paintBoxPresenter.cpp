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
  } else if (User::getInstance()->MouseType == MouseType::Cursor) {
    ChooseObj(event->pos());
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

  const Storage<Chunk*>& selections = model_->getAllSelections();
  for (const auto& obj : selections) {
    PaintSelection(obj);
  }
}

void PaintBoxPresenter::AddObj(QPoint pos) {
  lastPos_ = pos;
  int rad = User::getInstance()->BrushSize / 2;
  QPoint circlePos(pos.x() - rad, pos.y() - rad);
  CCircle* circle = new CCircle(circlePos, rad);
  model_->addCircleInBox(circle);

  QRect updateZone = circle->getBounds().adjusted(-2, -2, 2, 2);
  view_->update(updateZone);
}

void PaintBoxPresenter::PaintObj(const CCircle* obj) {
  QPainter painter(view_);
  QBrush br(obj->getColor());
  painter.setBrush(br);
  painter.setPen(obj->getColor());
  QRect rect(obj->getPos(), QSize(obj->getRad() * 2, obj->getRad() * 2));
  painter.drawEllipse(rect);
}

void PaintBoxPresenter::PaintSelection(const Chunk* selection) {
  QPainter painter(view_);
  painter.setPen(Qt::blue);
  painter.drawRect(selection->getArea());
}

void PaintBoxPresenter::ChooseObj(QPoint pos) {
  std::vector<Chunk*> choosedChunks = ChooseChunks(pos);

  for (const auto& chunk : choosedChunks) {
    if (chunk->isCircleInPoint(pos)) {
      model_->addSelection(chunk);

      QRect updateZone = chunk->getArea().adjusted(-2, -2, 2, 2);
      view_->update(updateZone);

      return; // DELETE to multiply seletion
    }
  }
}

std::vector<Chunk*> PaintBoxPresenter::ChooseChunks(QPoint pos) {
  std::vector<Chunk*> res;

  const std::vector<Chunk*>& chunks = model_->getChunks();

  for (int i = chunks.size() - 1; i >= 0; --i) {
    if (chunks[i]->hasPointIn(pos)) {
      res.emplace_back(chunks[i]);
    }
  }

  return res;
}
