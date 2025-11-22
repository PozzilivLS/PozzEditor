#include "hierarchy.h"

#include <QTreeView>

#include "TreeModel/treeModel.h"

Hierarchy::Hierarchy(QTreeView* tree) : tree_(tree) {
  QStringList headers;
  headers << "Объекты:";
  model_ = new TreeModel(headers, "");
  tree_->setModel(model_);
}

void Hierarchy::Update(Storage<Shape*> objects) {}
