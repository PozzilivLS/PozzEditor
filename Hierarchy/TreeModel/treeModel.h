#pragma once
#include <QAbstractItemModel>

class TreeItem;

class TreeModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  explicit TreeModel(const QStringList &headers, const QString &data, QObject *parent = nullptr);
  ~TreeModel();

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = {}) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = {}) const override;
  int columnCount(const QModelIndex &parent = {}) const override;

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  bool setHeaderData(int section, Qt::Orientation orientation,
                     const QVariant &value, int role = Qt::EditRole) override;

  bool insertColumns(int position, int columns,
                     const QModelIndex &parent = QModelIndex()) override;
  bool removeColumns(int position, int columns,
                     const QModelIndex &parent = QModelIndex()) override;
  bool insertRows(int position, int rows,
                  const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int position, int rows,
                  const QModelIndex &parent = QModelIndex()) override;
 private:
  static void setupModelData(const QStringList &lines, TreeItem *parent);
  TreeItem *getItem(const QModelIndex &index) const;

  TreeItem *rootItem_;
};
