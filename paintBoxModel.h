#pragma once

#include <vector>
#include <QPoint>

#include "Storage/storage.h";
#include <QRect>
#include <QObject>
#include "Observer/observer.h"

class Chunk;
class Object;

class PaintBoxModel {
 public:
  PaintBoxModel();
  ~PaintBoxModel();

  void AddObserver(PaintUpdatable *observer);
  void RemoveObserver(PaintUpdatable *observer);
  void NotifyAllObservers();

  void createChunk();
  void addObj(QPoint pos);
  bool chooseObj(QPoint pos);
  void resetSelection();
  void deleteSelections();

  const Storage<Chunk *> &getChunks() const;
  const Storage<Chunk *> &getAllSelections() const;
 
 private:
  void addShapeInLastBox(Object *object);
  void addSelection(Chunk *selection);
  void removeSelection(Chunk *selection);
  bool hasSelection(Chunk *selection);
  void deleteChunk(Chunk *chunk);
  void clearAllSelections();
  
  std::vector<Chunk *> chooseChunks(QPoint pos);

  std::vector<PaintUpdatable *> observers_;

  Storage<Chunk *> chunks_;
  Storage<Chunk *> selections_;
};
