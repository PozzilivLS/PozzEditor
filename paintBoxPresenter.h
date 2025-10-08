#pragma once
#include <QObject>

#include "PaintBox/paintbox.h"
#include "paintBoxModel.h"
class PaintBoxPresenter : public QObject {
  Q_OBJECT
 public:
  PaintBoxPresenter(QObject* parent = nullptr);

  void subscribeView(PaintBox* view);

 private slots:
  void onMousePress(QMouseEvent* event);
  void onMouseMove(QMouseEvent* event);

 private:
  PaintBox* view_ = nullptr;
  PaintBoxModel* model_ = nullptr;

  QPoint lastPos_;
  int epsilon_ = 5;
};
