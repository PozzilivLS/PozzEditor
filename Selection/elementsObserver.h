#pragma once

#include "Storage/storage.h"
#include "Shape/shape.h"

class ElementsObserver {
 public:
  virtual void chooseObjs(Storage<Shape *>& shapes) = 0;
  virtual void updateObjs(Storage<Shape *>& shapes) = 0;
  virtual ~ElementsObserver() {};
};