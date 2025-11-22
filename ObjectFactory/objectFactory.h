#pragma once
#include <QColor>
#include <QPoint>
#include <QSize>
#include <functional>

class Shape;

class ObjectFactory {
  using Creator = std::function<Shape*()>;

 public:
  ~ObjectFactory();

  ObjectFactory(const ObjectFactory& other) = delete;

  static ObjectFactory* getInstance();

  void registerType(const std::string& type, Creator cr);
  Shape* createObj(const std::string& type);

 private:
  ObjectFactory();
  static ObjectFactory* instance_;

  std::unordered_map<std::string, Creator> creators_;
};
