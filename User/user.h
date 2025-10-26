#pragma once
class User {
 public:
  ~User();

  User(const User& other) = delete;

  static User* getInstance();

  int BrushSize = 10;
  bool SingleDrawing = false;
 private:
  User();
  static User* instance_;
};
