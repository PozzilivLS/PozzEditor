#include "objectFactory.h"

ObjectFactory::ObjectFactory() {}

void ObjectFactory::registerType(const std::string& type, Creator cr) {
  creators_[type] = cr;
}

Shape * ObjectFactory::createObj(const std::string& type) {
  if (creators_.count(type) == 0) {
    return nullptr;
  }
  return creators_[type]();
}

ObjectFactory::~ObjectFactory() {}

ObjectFactory* ObjectFactory::getInstance() {
  if (!instance_) {
    instance_ = new ObjectFactory();
  }

  return instance_;
}

ObjectFactory* ObjectFactory::instance_ = nullptr;
