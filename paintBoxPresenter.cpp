#include "paintBoxPresenter.h"

#include <CCircle/ccircle.h>
#include <Chunk/chunk.h>
#include <User/user.h>

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
  QObject::connect(view_, SIGNAL(keyPress(QKeyEvent*)),
                   SLOT(onKeyPress(QKeyEvent*)));
}

void PaintBoxPresenter::onMousePress(QMouseEvent* event) {
  if (User::getInstance()->MouseType == MouseType::Brush) {
    model_->addChunk();
    addObj(event->pos());
  } else if (User::getInstance()->MouseType == MouseType::Cursor) {
    if (QApplication::keyboardModifiers() &
        Qt::ControlModifier) {  // TODO: refactor
      if (!chooseObj(event->pos())) {
        resetSelection();
      }
    } else {
      resetSelection();
      chooseObj(event->pos());
    }
  }
}

void PaintBoxPresenter::onMouseMove(QMouseEvent* event) {
  if (User::getInstance()->MouseType == MouseType::Brush &&
      !User::getInstance()->SingleDrawing) {
    if ((lastPos_ - event->pos()).manhattanLength() >= epsilon_) {
      addObj(event->pos());
    }
  }
}

void PaintBoxPresenter::onPaint(QPaintEvent* event) {
  const Storage<CCircle*>& objects = model_->getAllObj();
  for (const auto& obj : objects) {
    paintObj(obj);
  }

  const Storage<Chunk*>& selections = model_->getAllSelections();
  for (const auto& obj : selections) {
    paintSelection(obj);
  }
}

void PaintBoxPresenter::onKeyPress(QKeyEvent* event) {
  if (event->key() == Qt::Key_Delete) {
    deleteSelections();
  }
}

void PaintBoxPresenter::addObj(QPoint pos) {
  lastPos_ = pos;
  int rad = User::getInstance()->BrushSize / 2;
  QPoint circlePos(pos.x() - rad, pos.y() - rad);
  CCircle* circle = new CCircle(circlePos, rad);
  model_->addCircleInBox(circle);

  QRect updateZone = circle->getBounds().adjusted(-2, -2, 2, 2);
  view_->update(updateZone);
}

void PaintBoxPresenter::paintObj(const CCircle* obj) {
  QPainter painter(view_);
  QBrush br(obj->getColor());
  painter.setBrush(br);
  painter.setPen(obj->getColor());
  QRect rect(obj->getPos(), QSize(obj->getRad() * 2, obj->getRad() * 2));
  painter.drawEllipse(rect);
}

void PaintBoxPresenter::paintSelection(const Chunk* selection) {
  QPainter painter(view_);
  painter.setPen(Qt::blue);
  painter.drawRect(selection->getArea());
}

bool PaintBoxPresenter::chooseObj(QPoint pos) {
  bool res = false;

  std::vector<Chunk*> choosedChunks = chooseChunks(pos);

  for (const auto& chunk : choosedChunks) {
    if (chunk->isCircleInPoint(pos)) {
      if (!model_->hasSelection(chunk)) {
        model_->addSelection(chunk);
      } else {
        model_->removeSelection(chunk);
      }

      QRect updateZone = chunk->getArea().adjusted(-2, -2, 2, 2);
      view_->update(updateZone);

      res = true;
      return true;  // DELETE to multiply seletion
    }
  }

  return res;
}

std::vector<Chunk*> PaintBoxPresenter::chooseChunks(QPoint pos) {
  std::vector<Chunk*> res;

  const std::vector<Chunk*>& chunks = model_->getChunks();

  for (int i = chunks.size() - 1; i >= 0; --i) {
    if (chunks[i]->hasPointIn(pos)) {
      res.emplace_back(chunks[i]);
    }
  }

  return res;
}

void PaintBoxPresenter::resetSelection() {
  model_->clearAllSelections();
  view_->update();
}

void PaintBoxPresenter::deleteSelections() {
  const Storage<Chunk*>& selections = model_->getAllSelections();

  for (const auto& chunk : selections) {
    model_->deleteChunk(chunk);
  }

  model_->clearAllSelections();
  view_->update();
}
