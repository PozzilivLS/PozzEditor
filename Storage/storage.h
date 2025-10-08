#pragma once

#include <vector>

template <typename T>
class Storage {
  using ElementType = T;

 public:
  Storage();
  ~Storage();

  void addElement(const T& el);
  void removeElement(const T& el);
  size_t size() const;

  T& operator[](size_t index);
 private:
  std::vector<T> data_;
};

template <typename T>
Storage<T>::Storage() {}

template <typename T>
Storage<T>::~Storage() {}

template <typename T>
void Storage<T>::addElement(const T& el) {
  data_.emplace_back(el);
}

template <typename T>
void Storage<T>::removeElement(const T& el) {
  auto iter = std::find(data_.begin(), data_.end(), el);
  data_.erase(iter);
}

template <typename T>
size_t Storage<T>::size() const {
  return data_.size();
}

template <typename T>
T& Storage<T>::operator[](size_t index) {
  return data_[index];
}