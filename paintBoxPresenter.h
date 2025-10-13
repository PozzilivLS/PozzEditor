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
  void onKeyPress(QKeyEvent* event);

 private:
  void addObj(QPoint pos);
  void paintObj(const CCircle* obj);
  void paintSelection(const Chunk* selection);
  void chooseObj(QPoint pos);
  std::vector<Chunk*> chooseChunks(QPoint pos);
  void resetSelection();
  void deleteSelections();

  PaintBox* view_ = nullptr;
  PaintBoxModel* model_ = nullptr;

  QPoint lastPos_;
  int epsilon_ = 5;
};
