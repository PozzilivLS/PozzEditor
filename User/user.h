#pragma once
#include "Shape/shape.h"
#include <QColor>

class User {
 public:
  ~User();

  User(const User& other) = delete;

  static User* getInstance();

  int BrushSize = 10;
  std::string ShapeCreatorType = "None";
  QColor Color = QColor(100, 100, 100);
 private:
  User();
  static User* instance_;
};
