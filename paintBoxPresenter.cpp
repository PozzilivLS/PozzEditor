#include "paintBoxPresenter.h"

#include <QColor>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QResizeEvent>
#include <QPainter>

#include "Chunk/chunk.h"
#include "Mouse/mouse.h"
#include "PaintBox/paintbox.h"
#include "Shape/shape.h"
#include "User/user.h"
#include "paintBoxModel.h"

PaintBoxPresenter::PaintBoxPresenter(QObject* parent)
    : QObject(parent), model_(new PaintBoxModel()) {
  model_->addObserver(this);
}

void PaintBoxPresenter::subscribeView(
    PaintBox* view) {  // TODO: View can be null
  view_ = view;
  QObject::connect(view_, SIGNAL(mousePress(QMouseEvent*)),
                   SLOT(onMousePress(QMouseEvent*)));
  QObject::connect(view_, SIGNAL(mouseMove(QMouseEvent*)),
                   SLOT(onMouseMove(QMouseEvent*)));
  QObject::connect(view_, SIGNAL(mouseRelease(QMouseEvent*)),
                   SLOT(onMouseRelease(QMouseEvent*)));
  QObject::connect(view_, SIGNAL(paint(QPaintEvent*)),
                   SLOT(onPaint(QPaintEvent*)));
  QObject::connect(view_, SIGNAL(keyPress(QKeyEvent*)),
                   SLOT(onKeyPress(QKeyEvent*)));
  QObject::connect(view_, SIGNAL(hoverMove(QHoverEvent*)),
                   SLOT(onHoverMove(QHoverEvent*)));
  QObject::connect(view_, SIGNAL(hoverLeave(QHoverEvent*)),
                   SLOT(onHoverLeave(QHoverEvent*)));
  QObject::connect(view_, SIGNAL(resize(QResizeEvent*)),
                   SLOT(onResize(QResizeEvent*)));
}

void PaintBoxPresenter::setMouseType(Mouse* type) {
  mouseType_ = type;
  mouseType_->setModel(model_);

  model_->resetSelection();
}

void PaintBoxPresenter::updateZone() {
  //const Selection &selections = model_->getAllSelections();  // TODO: !!!!!!! NEEEEEED REFACTOR !!!!!!!
  //if (selections.size() > 0) {
  //  emit hasSelections(selections[selections.size() - 1]->getColor());
  //}

  view_->update();
}

bool PaintBoxPresenter::tryChangeColor(QColor color) {
  return model_->tryChangeColorForSelected(color);
}

void PaintBoxPresenter::onMousePress(QMouseEvent* event) {
  if (mouseType_) {
    mouseType_->onMousePress(event);
  }
}

void PaintBoxPresenter::onMouseMove(QMouseEvent* event) {
  if (mouseType_) {
    mouseType_->onMouseMove(event);
  }
}

void PaintBoxPresenter::onMouseRelease(QMouseEvent* event) {
  if (mouseType_) {
    mouseType_->onMouseRelease(event);
  }
}

void PaintBoxPresenter::onHoverMove(QHoverEvent* event) {
  if (mouseType_) {
    mouseType_->onHoverMove(event);
  }
}

void PaintBoxPresenter::onHoverLeave(QHoverEvent* event) {
  if (mouseType_) {
    mouseType_->onHoverLeave(event);
  }
}

void PaintBoxPresenter::onPaint(QPaintEvent* event) {
  const Storage<Shape*>& shapes = model_->getObjects();
  for (const auto& shape : shapes) {
    view_->paintObj(shape);
  }

  const Selection &s = model_->getAllSelections();
  view_->paintSelection(s);
}

void PaintBoxPresenter::onKeyPress(QKeyEvent* event) {
  if (event->key() == Qt::Key_Delete) {
    model_->deleteSelections();
  }

  {
    int xMover = (event->key() == Qt::Key_Right) - (event->key() == Qt::Key_Left);
    int yMover = (event->key() == Qt::Key_Down) - (event->key() == Qt::Key_Up);
    model_->moveSelections(xMover, yMover);
  }
}

void PaintBoxPresenter::onResize(QResizeEvent* event) {
  model_->calculateEdges(event->size());
}
