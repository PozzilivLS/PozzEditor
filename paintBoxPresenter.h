#pragma once
#include <QObject>

#include "PaintBox/paintbox.h"
#include "Chunk/chunk.h"
#include "paintBoxModel.h"
class PaintBoxPresenter : public QObject {
  Q_OBJECT
 public:
  PaintBoxPresenter(QObject* parent = nullptr);

  void subscribeView(PaintBox* view);

 private slots:
  void onMousePress(QMouseEvent* event);
  void onMouseMove(QMouseEvent* event);
  void onPaint(QPaintEvent* event);

 private:
  void AddObj(QPoint pos);
  void PaintObj(const CCircle* obj);
  void PaintSelection(const Chunk* selection);
  void ChooseObj(QPoint pos);
  std::vector<Chunk*> ChooseChunks(QPoint pos);

  PaintBox* view_ = nullptr;
  PaintBoxModel* model_ = nullptr;

  QPoint lastPos_;
  int epsilon_ = 5;
};
