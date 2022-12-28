#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[r];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    this->rows[i] = new IntArray(rhs[i]);
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray *[rhs.numRows];
    for (int i = 0; i < numRows; i++) {
      this->rows[i] = new IntArray(rhs[i]);
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return this->numRows;
}
int IntMatrix::getColumns() const {
  return this->numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < this->numRows && index >= 0);
  return *this->rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index < this->numRows && index >= 0);
  return *this->rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (rhs.numColumns != this->numColumns || rhs.numRows != this->numRows)
    return false;
  for (int i = 0; i < numRows; i++) {
    if ((*this)[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}
IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(this->numRows == rhs.numRows);
  assert(this->numColumns == rhs.numColumns);
  IntMatrix res(numRows, numColumns);
  for (int i = 0; i < this->numRows; i++) {
    for (int j = 0; j < this->numColumns; j++) {
      res[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return res;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
    else {
      s << " ]";
    }
  }
  if (rhs.getRows() == 0)
    s << " ]";
  return s;
}
