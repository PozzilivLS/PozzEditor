#pragma once
#include "./Storage/storage.h"
#include <QPixmap>
#include <QBitmap>

#include "./Shape/ellipse.h"

class QPoint;

class Chunk : public Storage<Ellipse*>, public Shape {
 public:
  Chunk(QColor color = Qt::red);
  ~Chunk() override;

  void addElement(Ellipse* const& el) override;

  void move(int x, int y) override;

  ShapeType type() const override { return ShapeType::Chunk; }
  bool hasPointIn(QPoint point) const override;
  bool isCircleInPoint(QPoint point) const;

  void draw(QPainter& painter) const override;

  void changeColor(QColor color) override;

  QPixmap& getPixmap();
  const QPixmap& getPixmap() const;

  bool isFixed() const;
  void setFixed();
 private:
  QPixmap cache_;
  QBitmap mask_;

  QPoint diffPos_;

  bool isFixed_ = false;
};
