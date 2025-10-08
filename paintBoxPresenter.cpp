#include "paintBoxPresenter.h"

#include <CCircle/ccircle.h>

#include <QMouseEvent>

PaintBoxPresenter::PaintBoxPresenter(QObject* parent)
    : QObject(parent), model_(new PaintBoxModel()) {}

void PaintBoxPresenter::subscribeView(PaintBox* view) {
  view_ = view;
  QObject::connect(view_, SIGNAL(mousePress(QMouseEvent*)),
                   SLOT(onMousePress(QMouseEvent*)));
  QObject::connect(view_, SIGNAL(mouseMove(QMouseEvent*)),
                   SLOT(onMouseMove(QMouseEvent*)));
}

void PaintBoxPresenter::onMousePress(QMouseEvent* event) {
  lastPos_ = event->pos();
  CCircle* circle = new CCircle(view_, 30, event->pos());
  circle->show();
  model_->addChunk();
  model_->addCircleInBox(circle);
}

void PaintBoxPresenter::onMouseMove(QMouseEvent* event) {
  if ((lastPos_ - event->pos()).manhattanLength() >= epsilon_) {
    CCircle* circle = new CCircle(view_, 30, event->pos());
    circle->show();
    model_->addCircleInBox(circle);
    lastPos_ = event->pos();
  }
}
