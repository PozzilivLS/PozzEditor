#pragma once
#include <PaintBox/paintbox.h>
#include <paintBoxModel.h>
class PaintBoxPresenter {
 public:
  PaintBoxPresenter() = delete;
  PaintBoxPresenter(PaintBox* view, PaintBoxModel* model);

  void mousePress(QMouseEvent* event);
  void mouseMove(QMouseEvent* event);
 private:
  PaintBox* const view_ = nullptr;
  PaintBoxModel* const model_ = nullptr;
};
