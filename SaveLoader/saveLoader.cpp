#include "saveLoader.h"

#include <QDebug>

#include "ObjectFactory/objectFactory.h"
#include "Shape/shape.h"

void SaveLoader::save(std::string fileName, Storage<Shape *>& objects) const {
  FILE* file = nullptr;
  fopen_s(&file, fileName.c_str(), "w+");

  for (const auto& obj : objects) {
    obj->save(file);
  }

  fclose(file);
}

void SaveLoader::load(std::string fileName, Storage<Shape *>& objects) {
  FILE* file = nullptr;
  fopen_s(&file, fileName.c_str(), "r+");
  char type[128];

  while (fscanf_s(file, "%s", type, (unsigned)_countof(type)) != EOF) {
    Shape * obj = ObjectFactory::getInstance()->createObj(type);
    if (!obj) continue;

    obj->load(file);

    objects.addElement(obj);
  }

  fclose(file);
}
