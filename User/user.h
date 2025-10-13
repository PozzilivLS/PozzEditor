#pragma once
enum class MouseType {
  Cursor = 0,
  Brush = 1
};

class User {
 public:
  ~User();

  User(const User& other) = delete;

  static User* getInstance();

  int BrushSize = 10;
  MouseType MouseType = MouseType::Cursor;
  bool SingleDrawing = false;
  bool CtrlModifierPressed = false;
 private:
  User();
  static User* instance_;
};
