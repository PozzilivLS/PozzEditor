#include "hierarchy.h"

#include <Shape/group.h>

#include <QApplication>
#include <QTreeView>

#include "TreeModel/treeModel.h"

Hierarchy::Hierarchy(QTreeView* tree) : tree_(tree) {
  QStringList headers;
  headers << "Объекты:";
  model_ = new TreeModel(headers, "");
  tree_->setModel(model_);

  connect(tree_, &QTreeView::clicked, this,
          &Hierarchy::onShapeSelected);
}

void Hierarchy::chooseObjs(Storage<Shape *>& shapes) {
  selectedShapes_ = shapes;
  tree_->selectionModel()->clearSelection();

  for (auto& shape : shapes) {
    tree_->selectionModel()->select(items_[shape->getId()],
                                    QItemSelectionModel::Select);
  }
}

void Hierarchy::updateObjs(Storage<Shape *>& shapes) {
  shapes_ = shapes;

  if (model_->rowCount() > 0) model_->removeRows(0, model_->rowCount());

  for (auto& shape : shapes) {
    processNode(shape);
  }
}

void Hierarchy::addObserver(ElementsObserver* observer) {
  observers_.addElement(observer);
}

void Hierarchy::notifyAllObservers() {
  for (auto& observer : observers_) {
    observer->chooseObjs(selectedShapes_);
  }
}

void Hierarchy::processNode(Shape * shape, QModelIndex index) {
  model_->insertRow(model_->rowCount(index), index);
  QModelIndex child = model_->index(model_->rowCount(index) - 1, 0, index);
  model_->setData(child, QVariant(shape->type()));
  items_[shape->getId()] = child;

  if (dynamic_cast<Group *>(shape)) {
    Storage<Shape *>& gr = static_cast<Group *>(shape)->getAllObj();
    for (auto& sh : gr) {
      processNode(sh, child);
    }
  }
}

void Hierarchy::onShapeSelected(const QModelIndex& index) {
  if (!(QApplication::keyboardModifiers() & Qt::ControlModifier)) {
    selectedShapes_.clear();
  }

  int id;
  for (auto& idIndex : items_) {
    if (idIndex.second == index) {
      id = idIndex.first;
      break;
    }
  }

  bool founded = false;
  for (auto& shape : shapes_) {
    if (shape->getId() == id) {
      if (selectedShapes_.hasElement(shape)) {
        selectedShapes_.removeElement(shape);
      } else {
        selectedShapes_.addElement(shape);
      }
      break;
    }
  }

  tree_->selectionModel()->clearSelection();
  for (auto& shape : selectedShapes_) {
    tree_->selectionModel()->select(items_[shape->getId()], QItemSelectionModel::Select);
  }

  notifyAllObservers();
}