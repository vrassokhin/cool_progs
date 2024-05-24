#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T> 
class MyVector {
private:
  T* data;
  size_t size;
  size_t capacity;

public:
  MyVector();
  ~MyVector();
  MyVector(MyVector const& copy);
  MyVector& operator=(const MyVector& other);

  size_t getSize() const;
  size_t getCapacity() const;
  T& operator[](size_t index);
  T& operator[](size_t index) const;

  void push_back(const T& newElement);
  void pop_back();
  void quicksort(T* start, T* end);
  void sort();
  
  template <typename U>
  friend std::ostream& operator<<(std::ostream& out, const MyVector<U>& MyVector);

  bool operator==(const MyVector& other) const;
  bool operator>(const MyVector& other) const;
  bool operator<(const MyVector& other) const;
  bool operator!=(const MyVector& other) const;
  bool operator>=(const MyVector& other) const;
  bool operator<=(const MyVector& other) const;

  class iterator {
  private:
    T* ptr;

  public:
    iterator(T* p) : ptr(p) {}

    T& operator*() const {
      return *ptr;
    }

    iterator& operator++() {
      ++ptr;
      return *this;
    }
    
    bool operator==(const iterator& other) const {
      return ptr == other.ptr;
    }

    bool operator!=(const iterator& other) const {
      return ptr != other.ptr;
    }
  };

  iterator begin();
  iterator end();
  iterator begin() const;
  iterator end() const;
};

template <typename T>
MyVector<T>::MyVector() : data(nullptr), size(0), capacity(0) {}

template <typename T>
MyVector<T>::~MyVector() { delete[] data; }

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : 
  size(other.size), 
  capacity(other.capacity) 
{
  data = new T[capacity];
  for (size_t i = 0; i < size; ++i) {
    data[i] = other.data[i];
  }
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
  if (this != &other) {
    size = other.size;
    capacity = other.capacity;
    delete[] data;
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
      data[i] = other.data[i];
    }
  }
  return *this;
}

template <typename T>
size_t MyVector<T>::getSize() const {
  return size;
}

template <typename T>
size_t MyVector<T>::getCapacity() const {
  return capacity;
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }
  return data[index]; 
}

template <typename T>
T& MyVector<T>::operator[](size_t index) const {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }
  return data[index]; 
}

template <typename T>
void MyVector<T>::push_back(const T& newElement) {
  if (size == capacity) {
    capacity = (capacity == 0) ? 1 : capacity * 2;

    T* newData = new T[capacity];
    for (size_t i = 0; i < size; i++) {
      newData[i] = data[i];
    }

    delete[] data;
    
    data = new T[capacity];
    for (size_t i = 0; i < size; i++) {
      data[i] = newData[i];
    }
    
    delete[] newData;
  }

  data[size++] = newElement;
}

template <typename T>
void MyVector<T>::pop_back() {
  if (size > 0) {
    --size;

    if (size < capacity / 2 && capacity > 1) {
      capacity /= 2;

      T* newData = new T[capacity];
      for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
      }

      delete[] data;
      
      data = new T[capacity];
      for (size_t i = 0; i < size; i++) {
        data[i] = newData[i];
      }
      
      delete[] newData;
    }
  }
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() {
  return iterator(data);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() {
  return iterator(data + size);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() const {
  return iterator(data);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() const {
  return iterator(data + size);
}

template <typename T>
void MyVector<T>::quicksort(T* start, T* end) {
  if (start < end) {
    T* pivot = start;
    T* left = start + 1;
    T* right = end;

    while (left <= right) {
      while (left <= end && *left < *pivot) {
        ++left;
      }
      while (right > start && *right >= *pivot) {
        --right;
      }
      if (left < right) {
        std::swap(*left, *right);
      }
    }

    std::swap(*pivot, *right);

    quicksort(start, right - 1);
    quicksort(right + 1, end);
  }
}

template <typename T>
void MyVector<T>::sort() {
  quicksort(data, data + size - 1);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& MyVector) {
  out << "{";

  auto it = MyVector.begin();

  if (it != MyVector.end()) {
    out << *it;
    ++it;
  }

  while (it != MyVector.end()) {
    out << "," << *it;
    ++it;
  }

  out << "}";

  return out;
}

template <typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
  if (size != other.size)
    return false;
  
  auto it = begin();
  auto it_other = other.begin();
  
  while (it != end() && it_other != other.end()) {
    if (*it != *it_other)
      return false;
    ++it;
    ++it_other;
  }
  
  return true;
}

template <typename T>
bool MyVector<T>::operator>(const MyVector& other) const {
  auto it = begin();
	auto it_other = other.begin();
	
  while (it != end() && it_other != other.end()) {
		if (*it != *it_other)
			return *it > *it_other;
		++it;
		++it_other;
	}

	return (it != end() && it_other == other.end());
}

template <typename T>
bool MyVector<T>::operator<(const MyVector& other) const {
  auto it = begin();
	auto it_other = other.begin();
	
  while (it != end() && it_other != other.end()) {
		if (*it != *it_other)
			return *it < *it_other;
		++it;
		++it_other;
	}

	return (it == end() && it_other != other.end());
}

template <typename T>
bool MyVector<T>::operator!=(const MyVector& other) const {
  return !(*this == other);
}

template <typename T>
bool MyVector<T>::operator>=(const MyVector& other) const {
  return !(*this < other);
}

template <typename T>
bool MyVector<T>::operator<=(const MyVector& other) const {
  return !(*this > other);
}