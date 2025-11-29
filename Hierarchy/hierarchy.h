#pragma once
#include <QStandardItemModel>

#include "Selection/elementsObserver.h"

class QTreeView;
class TreeModel;

class Hierarchy : public ElementsObserver, public QObject {
 public:
  Hierarchy(QTreeView *tree);

  void chooseObjs(Storage<Shape *> &shapes) override;
  void updateObjs(Storage<Shape *> &shapes) override;

  void addObserver(ElementsObserver *o);
  void notifyAllObservers();

 private slots:
  void onShapeSelected(const QModelIndex &index);

 private:
  void processNode(Shape *sh, QModelIndex index = QModelIndex());

  QTreeView *tree_ = nullptr;
  TreeModel *model_ = nullptr;

  Storage<ElementsObserver *> observers_;

  Storage<Shape *> shapes_;
  Storage<Shape *> selectedShapes_;

  std::unordered_map<int, QModelIndex> items_;
};
