#pragma once

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
  virtual bool hasElement(const T& el);
  virtual const T& last();
  virtual void clear();
  size_t size() const;

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

 protected:
  std::vector<T> data_;
};

template <typename T>
Storage<T>::Storage() {}

template <typename T>
Storage<T>::~Storage() {
}

template <typename T>
void Storage<T>::addElement(const T& el) {
  data_.emplace_back(el);
}

template <typename T>
void Storage<T>::removeElement(const T& el) {
  data_.erase(std::remove(data_.begin(), data_.end(), el), data_.end());
}

template <typename T>
inline void Storage<T>::removeElementByIndex(const int index) {
  if (index < size() && index >= 0)
    data_.erase(data_.begin() + index);
}

template <typename T>
inline bool Storage<T>::hasElement(const T& el) {
  auto iter = std::find(data_.begin(), data_.end(), el);
  return iter != data_.end();
}

template <typename T>
size_t Storage<T>::size() const {
  return data_.size();
}

template <typename T>
void Storage<T>::clear() {
  data_.clear();
}

template <typename T>
const T& Storage<T>::last() {
  return data_.back();
}

template <typename T>
T& Storage<T>::operator[](size_t index) {
  return data_[index];
}

template <typename T>
const T& Storage<T>::operator[](size_t index) const {
  return data_[index];
}