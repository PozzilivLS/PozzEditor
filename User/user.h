#pragma once
class User {
 public:
  ~User();

  User(const User& other) = delete;

  static User* getInstance();

  int BrushSize = 10;
 private:
  User();
  static User* instance_;
};
