#pragma once
#include "shape.h"
#include "Storage/storage.h"

class Group : public Shape {
 public:
  Group(Storage<Shape *> storage);
  ~Group();

  void move(int x, int y) override;
  void resize(int x, int y) override;

  void changeColor(QColor color) override;

  const char *type() const override { return "Group"; }

  QRect getBounds() const override;

  bool hasPointIn(QPoint point) const override;

  void draw(QPainter &painter) const override;

  void save(FILE *file) override;
  void load(FILE *file) override;

  Storage<Shape *>& getAllObjToUngroup();
 private:
  void updateRelativeInfo();

  Storage<Shape *> objects_;

  std::unordered_map<Shape *, std::pair<QPointF, QSizeF>> relativeInfo_;
};
