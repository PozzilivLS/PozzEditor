#include "paintBoxPresenter.h"

#include <QMouseEvent>
#include <QPainter>

#include "Chunk/chunk.h"
#include "PaintBox/paintbox.h"
#include "Shape/shape.h"
#include "User/user.h"
#include "paintBoxModel.h"
#include "Mouse/mouse.h"

PaintBoxPresenter::PaintBoxPresenter(QObject* parent)
    : QObject(parent), model_(new PaintBoxModel()) {
  model_->AddObserver(this);
}

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

void PaintBoxPresenter::setMouseType(Mouse* type) {
  mouseType_ = type;
  mouseType_->setModel(model_);
}

void PaintBoxPresenter::updateZone() { view_->update(); }

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

void PaintBoxPresenter::onPaint(QPaintEvent* event) {
  const Storage<Chunk*>& chunks = model_->getChunks();

  if (chunks.size() == 0) {
    return;
  }

  for (int i = 0; i < chunks.size() - 1; i++) {
    view_->paintChunk(chunks[i]);
  }

  for (const auto& obj : *chunks[chunks.size() - 1]) {
    view_->paintObj(obj, chunks[chunks.size() - 1]->getPixmap());
  }
  view_->paintChunk(chunks[chunks.size() - 1]);

  const Storage<Chunk*>& selections = model_->getAllSelections();
  for (const auto& chunk : selections) {
    view_->paintSelection(chunk);
  }
}

void PaintBoxPresenter::onKeyPress(QKeyEvent* event) {
  if (event->key() == Qt::Key_Delete) {
    model_->deleteSelections();
  }
}
