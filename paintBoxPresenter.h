#pragma once
#include <QObject>
#include <QPoint>

#include "Observer/observer.h"

class PaintBox;
class Chunk;
class PaintBoxModel;
class Shape;
class Mouse;

class QMouseEvent;
class QPaintEvent;
class QKeyEvent;

class PaintBoxPresenter : public QObject, PaintUpdatable {
  Q_OBJECT
 public:
  PaintBoxPresenter(QObject* parent = nullptr);

  void subscribeView(PaintBox* view);
  void setMouseType(Mouse* type);

  void updateZone() override;

  bool tryChangeColor(QColor color);

 private slots:
  void onMousePress(QMouseEvent* event);
  void onMouseMove(QMouseEvent* event);
  void onPaint(QPaintEvent* event);
  void onKeyPress(QKeyEvent* event);

 private:
  Mouse* mouseType_ = nullptr;

  PaintBox* view_ = nullptr;
  PaintBoxModel* model_ = nullptr;
};
