#include "cursor.h"

#include <QMouseEvent>
#include <QApplication>

#include "User/user.h"
#include "paintBoxModel.h"

void Cursor::onMousePress(QMouseEvent* event) {
  if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
    if (!model_->selectObj(event->pos())) {
      model_->resetSelection();
    }
  } else {
    model_->resetSelection();
    model_->selectObj(event->pos());
  }
  lastPos_ = event->pos();
}

void Cursor::onMouseMove(QMouseEvent* event) {
  QPoint diff = event->pos() - lastPos_;
  model_->moveSelections(diff.x(), diff.y());
  lastPos_ = event->pos();
}

void Cursor::onMouseRelease(QMouseEvent* event) {}
