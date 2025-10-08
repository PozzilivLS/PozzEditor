#pragma once

#include <vector>

template <typename T>
class Storage {
  using Type = T;

 public:
  Storage();

  void addElement(T& el);
  void removeElement(T& el);
  size_t size();

 private:
  std::vector<T> data_;
};
