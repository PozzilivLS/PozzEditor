#include "objectFactory.h"

#include "Chunk/chunk.h"
#include "Shape/ellipse.h"
#include "Shape/line.h"
#include "Shape/rect.h"
#include "Shape/triangle.h"
#include "Shape/group.h"

ObjectFactory::ObjectFactory() {
  creators_["Rect"] = []() { return new Rect(); };
  creators_["Ellipse"] = []() { return new Ellipse(); };
  creators_["Triangle"] = []() { return new Triangle(); };
  creators_["Line"] = []() { return new Line(); };
  creators_["Chunk"] = []() { return new Chunk(); };
  creators_["Group"] = []() { return new Group(Storage<Shape *>()); };
}

Shape* ObjectFactory::createObj(std::string type) { return creators_[type](); }

ObjectFactory::~ObjectFactory() {
  if (instance_) {
    delete instance_;
    instance_ = nullptr;
  }
}

ObjectFactory* ObjectFactory::getInstance() {
  if (!instance_) {
    instance_ = new ObjectFactory();
  }

  return instance_;
}

ObjectFactory* ObjectFactory::instance_ = nullptr;
