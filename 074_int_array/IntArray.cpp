#include "IntArray.h"

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) {
  numElements = n;
  data = new int[n];
}

IntArray::IntArray(const IntArray & rhs) {
  this->numElements = rhs.numElements;
  this->data = new int[rhs.numElements];
  for (int i = 0; i < rhs.numElements; i++) {
    this->data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  delete[] this->data;
  this->numElements = rhs.numElements;
  this->data = new int[rhs.numElements];
  for (int i = 0; i < rhs.numElements; i++) {
    this->data[i] = rhs.data[i];
  }

  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index < this->numElements);
  return this->data[index];
}
int & IntArray::operator[](int index) {
  assert(index < this->numElements);
  return this->data[index];
}

int IntArray::size() const {
  return this->numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (rhs.numElements != this->numElements)
    return false;
  for (int i = 0; i < rhs.numElements; i++) {
    if (this->data[i] != rhs.data[i])
      return false;
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  if (rhs.size() == 0)
    s << "}";
  else {
    for (int i = 0; i < rhs.size() - 1; i++) {
      s << rhs[i] << ", ";
    }
    s << rhs[rhs.size() - 1] << "}";
  }
  return s;
}
