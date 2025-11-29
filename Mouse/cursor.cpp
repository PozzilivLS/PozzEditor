#include "cursor.h"

#include <QApplication>
#include <QHoverEvent>
#include <QMouseEvent>

#include "User/user.h"
#include "PaintBox/paintBoxModel.h"

void Cursor::onMousePress(QMouseEvent* event) {
  lastPos_ = event->pos();
  isChanging_ = true;

  if (sizeChangeState_ == Selection::MousePosState::None) {
    if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
      if (!model_->selectObj(event->pos())) {
        model_->resetSelection();
      }
      return;
    }

    const Selection& s = model_->getAllSelections();
    if (!s.hasObjectInPoint(event->pos())) {
      model_->resetSelection();
      model_->selectObj(event->pos());
    }
  }
}

void Cursor::onMouseMove(QMouseEvent* event) {
  if (sizeChangeState_ == Selection::MousePosState::None) {
    QPoint diff = event->pos() - lastPos_;

    model_->moveSelections(diff.x(), diff.y());

    QPoint outside = model_->isInWindow(model_->getAllSelections().getArea());
    if (!outside.isNull()) {
      model_->moveSelections(outside.x(), outside.y());
    }
    lastPos_ = event->pos();
  } else {
    QPoint diff = event->pos() - lastPos_;

    model_->resizeSelections(diff.x(), diff.y());

    QPoint outside = model_->isInWindow(model_->getAllSelections().getArea());
    if (!outside.isNull()) {
      model_->resizeSelections(outside.x(), outside.y());
    }
    lastPos_ = event->pos();
  }
}

void Cursor::onMouseRelease(QMouseEvent* event) { isChanging_ = false; }

void Cursor::onHoverMove(QHoverEvent* event) {
  if (!isChanging_) {
    sizeChangeState_ =
        model_->checkSelectionBounds(event->position().toPoint());

    Qt::CursorShape newCursor = Qt::ArrowCursor;

    if (!QApplication::overrideCursor()) {
      QApplication::setOverrideCursor(newCursor);
    }

    switch (sizeChangeState_) {
      case Selection::MousePosState::BCorner:
        newCursor = Qt::SizeFDiagCursor;
        break;
      case Selection::MousePosState::FCorner:
        newCursor = Qt::SizeBDiagCursor;
        break;
      case Selection::MousePosState::HorEdge:
        newCursor = Qt::SizeVerCursor;
        break;
      case Selection::MousePosState::VerEdge:
        newCursor = Qt::SizeHorCursor;
        break;
      case Selection::MousePosState::None:
        newCursor = Qt::ArrowCursor;
        break;
    }
    QApplication::changeOverrideCursor(newCursor);
  }
}

void Cursor::onHoverLeave(QHoverEvent* event) {
  if (!isChanging_) {
    QApplication::restoreOverrideCursor();
  }
}
