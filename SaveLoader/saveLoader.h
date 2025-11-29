#pragma once
#include <string>

#include "Storage/storage.h"

class Shape;

class SaveLoader {
 public:
  void save(std::string fileName, Storage<Shape *>& objects) const;
  void load(std::string fileName, Storage<Shape *>& objects);
};
