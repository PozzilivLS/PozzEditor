#pragma once
#include "./Storage/storage.h"
#include <QPixmap>
#include <QBitmap>

#include "./Shape/object.h"

class QPoint;

class Chunk : public Storage<Object*>, public Object {
 public:
  ~Chunk() override;

  void addElement(Object* const& el) override;

  bool hasPointIn(QPoint point) const override;
  bool isCircleInPoint(QPoint point) const;

  QPixmap& getPixmap();
  const QPixmap& getPixmap() const;

 private:
  QPixmap cache_;
  QBitmap mask_;
};
