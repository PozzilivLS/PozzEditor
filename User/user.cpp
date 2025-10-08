#include "user.h"

User::~User() { instance_ = nullptr; }

User* User::getInstance() {
  if (!instance_) {
    instance_ = new User();
  }

  return instance_;
}

User::User() { }

User* User::instance_ = nullptr;
