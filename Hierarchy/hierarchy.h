#pragma once
#include <QStandardItemModel>

#include "Storage/storage.h"
#include "Shape/shape.h"

class QTreeView;
class TreeModel;

class Hierarchy {
 public:
  Hierarchy(QTreeView *tree);
  void Update(Storage<Shape *> objects);

 private:
  QTreeView *tree_ = nullptr;
  TreeModel *model_ = nullptr;
};
