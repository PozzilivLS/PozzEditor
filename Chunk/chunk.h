#pragma once
#include <QBitmap>
#include <QPixmap>

#include "./Shape/ellipse.h"
#include "./Storage/storage.h"

class QPoint;

class Chunk : public Storage<Ellipse*>, public Shape {
 public:
  Chunk(QColor color = Qt::red);
  ~Chunk() override;

  void addElement(Ellipse* const& el) override;

  void resize(int x, int y) override;

  const char* type() const override { return "Chunk"; }
  bool hasPointIn(QPoint point) const override;
  bool isCircleInPoint(QPoint point) const;

  void draw(QPainter& painter) const override;

  void changeColor(QColor color) override;

  QPixmap& getPixmap();
  const QPixmap& getPixmap() const;

  bool isFixed() const;
  void setFixed();

  void save(FILE* file) override;
  void load(FILE* file) override;

 private:
  QPixmap cache_;
  QPixmap fixedCache_;
  QBitmap mask_;

  bool isFixed_ = false;
};
