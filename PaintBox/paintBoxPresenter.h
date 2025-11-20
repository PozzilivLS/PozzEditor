#pragma once
#include <QObject>
#include <QPoint>
#include <QColor>

#include "Observer/observer.h"

class PaintBox;
class Chunk;
class PaintBoxModel;
class Shape;
class Mouse;

class QMouseEvent;
class QPaintEvent;
class QHoverEvent;
class QKeyEvent;
class QResizeEvent;

class PaintBoxPresenter : public QObject, PaintUpdatable {
  Q_OBJECT
 public:
  PaintBoxPresenter(QObject* parent = nullptr);

  void subscribeView(PaintBox* view);
  void setMouseType(Mouse* type);

  void updateZone() override;

  bool tryChangeColor(QColor color);

  void openFile();
  void saveFile();

 signals:
  void hasSelections(QColor color);

 private slots:
  void onMousePress(QMouseEvent* event);
  void onMouseMove(QMouseEvent* event);
  void onMouseRelease(QMouseEvent* event);
  void onHoverMove(QHoverEvent* event);
  void onHoverLeave(QHoverEvent* event);
  void onPaint(QPaintEvent* event);
  void onKeyPress(QKeyEvent* event);
  void onResize(QResizeEvent* event);
 
  void onGroup();
  void onUngroup();

 private:
  void showContextMenu(QPoint pos);

  Mouse* mouseType_ = nullptr;

  PaintBox* view_ = nullptr;
  PaintBoxModel* model_ = nullptr;
};
