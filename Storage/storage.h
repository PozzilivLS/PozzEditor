#pragma once

#include <cstddef>
#include <iterator>
#include <vector>

template <typename T>
class Storage {
  using StorageType = std::vector<T>;

 public:
  typename StorageType::iterator begin() { return data_.begin(); };
  typename StorageType::iterator end() { return data_.end(); };

  typename StorageType::const_iterator begin() const { return data_.begin(); };
  typename StorageType::const_iterator end() const { return data_.end(); };
  typename StorageType::const_iterator cbegin() const { return data_.cbegin(); };
  typename StorageType::const_iterator cend() const { return data_.cend(); };

  Storage();
  virtual ~Storage();

  virtual void addElement(const T& el);
  virtual void removeElement(const T& el);
  virtual void removeElementByIndex(const int index);
  size_t size() const;

  T& operator[](size_t index);

 protected:
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
inline void Storage<T>::removeElementByIndex(const int index) {
  data_.erase(data_.begin() + index);
}

template <typename T>
size_t Storage<T>::size() const {
  return data_.size();
}

template <typename T>
T& Storage<T>::operator[](size_t index) {
  return data_[index];
}