#include "storage.h"

template <typename T>
Storage<T>::Storage() {

}

template <typename T>
Storage<T>::~Storage() {}

template <typename T>
void Storage<T>::addElement(T& el) {
  data_.emplace_back(el);
}

template <typename T>
void Storage<T>::removeElement(T& el) {
  auto iter = std::find(data_.begin(), data_.end(), el);
  data_.erase(iter);
}

template <typename T>
size_t Storage<T>::size() {
  return data_.size();
}

template <typename T>
T& Storage<T>::operator[](size_t index) {
  return data_[index];
}