#include "cursor.h"

#include <QMouseEvent>
#include <QApplication>

#include "User/user.h"
#include "paintBoxModel.h"

void Cursor::onMousePress(QMouseEvent* event) {
  if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
    if (!model_->chooseObj(event->pos())) {
      model_->resetSelection();
    }
  } else {
    model_->resetSelection();
    model_->chooseObj(event->pos());
  }
}

void Cursor::onMouseMove(QMouseEvent* event) {}
