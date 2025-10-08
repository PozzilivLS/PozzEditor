#pragma once

#include <vector>

template <typename T>
class Storage {
  using ElementType = T;

 public:
  Storage();
  ~Storage();

  void addElement(T& el);
  void removeElement(T& el);
  size_t size();

  T& operator[](size_t index);
 private:
  std::vector<T> data_;
};
