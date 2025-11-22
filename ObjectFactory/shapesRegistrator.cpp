#include "shapesRegistrator.h"

#include "Chunk/chunk.h"
#include "Shape/ellipse.h"
#include "Shape/group.h"
#include "Shape/line.h"
#include "Shape/rect.h"
#include "Shape/triangle.h"
#include "objectFactory.h"

void ShapesRegistrator::registerTypes() {
  ObjectFactory::getInstance()->registerType("Rect",
                                             []() { return new Rect(); });
  ObjectFactory::getInstance()->registerType("Ellipse",
                                             []() { return new Ellipse(); });
  ObjectFactory::getInstance()->registerType("Triangle",
                                             []() { return new Triangle(); });
  ObjectFactory::getInstance()->registerType("Line",
                                             []() { return new Line(); });
  ObjectFactory::getInstance()->registerType("Chunk",
                                             []() { return new Chunk(); });
  ObjectFactory::getInstance()->registerType(
      "Group", []() { return new Group(Storage<Shape *>()); });
}
