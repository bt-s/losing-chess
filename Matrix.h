#ifndef matrix_h
#define matrix_h

/*
  Matrix implementation from lab 4.
*/

#include <iostream>
#include <cmath>
#include <cstring>

template <class T>
class Matrix {
public:
  // Default constructor
  Matrix();

  // Constructor: create 2D matrix of shape (x, x)
  explicit Matrix(unsigned int x);

  // Constructor: create 2D matrix of shape (x, y)
  Matrix(unsigned int x, unsigned int y);

  // Destructor: create 2D matrix of shape (x, y)
  ~Matrix();

  // Copy constructor
  Matrix(const Matrix& m);

  // Move constructor
  Matrix(Matrix&& m);

  // Initializer list constructor
  Matrix(std::initializer_list<T> il);

  // Assignment operator overloader
  Matrix& operator=(const Matrix& m);
  Matrix& operator=(Matrix&& m);

  // Function operator overloder to access elements of a matrix
  T& operator()(const unsigned int& row, const unsigned int& col);
  const T& operator()(const unsigned int& row, const unsigned int& col) const;

  // Equality operators overloading
  bool operator==(const Matrix& m);
  bool operator!=(const Matrix& m);

  // Arithmetic operators overloading
  Matrix operator+(const Matrix& m);
  Matrix operator+(const T& t);
  Matrix& operator+=(const Matrix& m);
  Matrix& operator+=(const T& t);
  Matrix operator-(const Matrix& m);
  Matrix operator-(const T& t);
  Matrix& operator-=(const Matrix& m);
  Matrix& operator-=(const T& t);
  // Matrix multiplication is implemented as the dot product
  Matrix operator*(const Matrix& m);
  Matrix operator*(const T& t);
  Matrix& operator*=(const Matrix& m);
  Matrix& operator*=(const T& t);

  // << overloader to be able to pretty print a matrix' contents to stdout
  template <class Y>
  friend std::ostream& operator<<(std::ostream& out, const Matrix<Y>& m);

  // Accessors
  unsigned int get_rows();
  unsigned int get_cols();
  unsigned int get_size();

  T get_element(unsigned int x, unsigned int y);
  const T get_element(unsigned int x, unsigned int y) const;

  // Methods
  static Matrix identity(unsigned int size);
  void set_element(unsigned int x, unsigned int y, T val );
  void reset();
  void resize(unsigned int r, unsigned int c);
  void transpose();
  void insert_row(unsigned int row);
  void append_row(unsigned int row);
  void remove_row(unsigned int row);
  void insert_col(unsigned int col);
  void append_col(unsigned int col);
  void remove_col(unsigned int col);

  // Iterators
  typedef T* iterator;
  typedef const T* const_iterator;

  iterator begin() {
    return &vec[0];
  }
  iterator end() {
    return &vec[0 + rows*cols];
  }

  const_iterator cbegin() {
    return &vec[0];
  }
  const_iterator cend() {
    return &vec[0 + rows*cols];
  }

  // Check if move constructible
  static_assert(std::is_move_constructible<T>::value,
      "Matrix elements must be both moveConstructible and moveAssignable");

  // Check if move assignable
  static_assert(std::is_move_assignable<T>::value,
      "Matrix elements must be both moveConstructible and moveAssignable");

private:
  size_t rows;
  size_t cols;
  size_t capacity;
  T *vec;
};

template <class T>
Matrix<T>::Matrix() {
  this->rows = 0;
  this->cols = 0;
  this->vec = new T[0];
}

template <class T>
Matrix<T>::Matrix(unsigned int x) {
  this->rows = x;
  this->cols = x;
  x > 0 ? this->vec = new T[x*x]{0} : this->vec = new T[x*x];
}

template <class T>
Matrix<T>::Matrix(unsigned int x, unsigned int y) {
  if (x > 0 && y > 0) {
    this->rows = x;
    this->cols = y;
    this->vec = new T[x*y]{0};
  }
  else {
    this->rows = 0;
    this->cols = 0;
    this->vec = new T[0];
  }
}

template <class T>
Matrix<T>::~Matrix() {
  if (this->vec) {
    delete[] this->vec;
  }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& m) {
  this->rows = m.rows;
  this->cols = m.cols;
  this->vec = new T[m.rows*m.cols];

  for(unsigned int r = 0; r < m.rows; r++) {
    for(unsigned int c = 0; c < m.cols; c++) {
      this->set_element(r, c, m.get_element(r, c));
    }
  }
}

template <class T>
Matrix<T>::Matrix(std::initializer_list<T> il) {
  unsigned int sr = sqrt(il.size());
  if (sr*sr == il.size()) {
    this->rows = sr;
    this->cols = sr;
    this->vec = new T[sr*sr];

    int i = 0;
    for (const auto& l : il) {
      this->vec[i] = l;
      ++i;
    }
  }
  else {
    throw std::out_of_range(
      "Initializer list not square: index is out of range"
    );
  }
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
  if (this != &m) {
    if (!(this->rows == m.rows && this->cols == m.cols)) {
      this->resize(m.rows, m.cols);
    }
    for(unsigned int r = 0; r < m.rows; r++) {
      for(unsigned int c = 0; c < m.cols; c++) {
        this->set_element(r, c, m.get_element(r, c));
      }
    }
  }
  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& m) {
  if (this != &m) {
    if (!(this->rows == m.rows && this->cols == m.cols)) {
      throw std::out_of_range("Unequal matrix dimensions: index is out of range");
    }

    delete[] this->vec;

    this->rows = m.rows;
    this->cols = m.rows;
    this->vec = m.vec;

    m.rows = 0;
    m.cols = 0;
    m.vec = nullptr;
  }
  return *this;
}

template <class T>
T& Matrix<T>::operator()(const unsigned int& x, const unsigned int& y) {
  if (x >= this->rows || y >= this->cols) {
    throw std::out_of_range("Element not found: index is out of range");
  }

  return this->vec[x * this->cols + y];
}
template <class T>
const T& Matrix<T>::operator()(const unsigned int& x, const unsigned int& y) const {
  return *this(x, y);
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& m) {
  int s1 = m.rows*m.cols;
  int s2 = this->rows*this->cols;
  if (s1 != s2) return false;

  while (s2--) {
    if (this->vec[s2] != m.vec[s2]) return false;
  }
  return true;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix<T>& m) {
  return !(*this == m);
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix& m) {
  if (this->rows != m.rows || this->cols != m.cols) {
    throw std::out_of_range(
      "Incompatible matrix dimensions: index is out of range"
    );
  }

  Matrix m_new = *this;

  int s = this->rows*this->cols;
  while (s--) {
    m_new.vec[s] += m.vec[s];
  }

  return m_new;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const T& t) {
  Matrix m_new = *this;

  int s = this->rows*this->cols;
  while (s--) {
    m_new.vec[s] += t;
  }

  return m_new;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& m) {
  if (this->rows != m.rows || this->cols != m.cols) {
    throw std::out_of_range(
      "Incompatible matrix dimensions: index is out of range"
    );
  }

  int s = this->rows*this->cols;
  while (s--) {
    this->vec[s] += m.vec[s];
  }

  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const T& t) {
  int s = this->rows*this->cols;
  while (s--) {
    this->vec[s] += t;
  }

  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix& m) {
  if (this->rows != m.rows || this->cols != m.cols) {
    throw std::out_of_range(
      "Incompatible matrix dimensions: index is out of range"
    );
  }

  Matrix m_new = *this;

  int s = this->rows*this->cols;
  while (s--) {
    m_new.vec[s] -= m.vec[s];
  }

  return m_new;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const T& t) {
  Matrix m_new = *this;

  int s = this->rows*this->cols;
  while (s--) {
    m_new.vec[s] -= t;
  }

  return m_new;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& m) {
  if (this->rows != m.rows || this->cols != m.cols) {
    throw std::out_of_range(
      "Incompatible matrix dimensions: index is out of range"
    );
  }

  int s = this->rows*this->cols;
  while (s--) {
    this->vec[s] -= m.vec[s];
  }

  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const T& t) {
  int s = this->rows*this->cols;
  while (s--) {
    this->vec[s] -= t;
  }

  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix& m) {
  if (this->cols != m.rows) {
    throw std::out_of_range(
      "Incompatible matrix dimensions: index is out of range"
    );
  }

  Matrix<T> m_res(this->rows, m.cols);

  for (unsigned int r = 0; r < this->rows; r++) {
    for (unsigned int c = 0; c < m.cols; c++) {
      T el = 0;
      for (unsigned int rm = 0; rm < m.rows; rm++) {
        el += (this->get_element(r, rm) * m.get_element(rm, c));
      }
      m_res.set_element(r, c, el);
    }
  }

  return m_res;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T& t) {
  Matrix m_new = *this;

  int s = this->rows * this->cols;
  while (s--) {
    m_new.vec[s] *= t;
  }

  return m_new;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix& m) {
  if (this->cols != m.rows) {
    throw std::out_of_range(
      "Incompatible matrix dimensions: index is out of range"
    );
  }

  Matrix<T> m_temp(this->rows, m.cols);

  for (unsigned int r = 0; r < rows; r++) {
    for (unsigned int c = 0; c < m.cols; c++) {
      T el = 0;
      for (unsigned int rm = 0; rm < m.rows; rm++) {
        el += (this->get_element(r, rm) * m.get_element(rm, c));
      }
      m_temp.set_element(r, c, el);
    }
  }

  *this = m_temp;

  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T& t) {
  int s = this->rows*this->cols;
  while (s--) {
    this->vec[s] *= t;
  }

  return *this;
}

template <class T>
unsigned int Matrix<T>::get_rows() {
  return this->rows;
}

template <class T>
unsigned int Matrix<T>::get_cols() {
  return this->cols;
}

template <class T>
unsigned int Matrix<T>::get_size() {
  if (this->cols == 0) {
    return (this->rows);
  }
  else if (this->rows == 0) {
    return (this->cols);
  }
  return (this->cols * this->rows);
}

template <class T>
T Matrix<T>::get_element(unsigned int x, unsigned int y) {
  if (x >= this->rows || y >= this->cols) {
    throw std::out_of_range("Element not found: index is out of range");
  }

  return this->vec[x * this->cols + y];
}

template <class T>
const T Matrix<T>::get_element(unsigned int x, unsigned int y) const {
  if (x >= this->rows || y >= this->cols) {
    throw std::out_of_range("Element not found: index is out of range");
  }

  return this->vec[x * this->cols + y];
}

template <class T>
void Matrix<T>::set_element(unsigned int x, unsigned int y, T val) {
  if (x >= this->rows || y >= this->cols) {
    throw std::out_of_range("Index is out of range");
  }

  this->vec[x * this->cols + y] = val;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m){
  for (unsigned int r = 0; r < m.rows; r++) {
    for (unsigned int c = 0; c < m.cols; c++) {
      os << m.vec[r * m.cols + c] << " ";
    }
    os << std::endl;
  }
  return os;
}

template <class T>
void Matrix<T>::insert_row(unsigned int row) {
  if (this->rows == 0 || this->cols == 0 || row > this->rows) {
    throw std::out_of_range(
      "Cannot carry out row operation: Index is out of range"
    );
  }
  this->rows++;
  T* old_vec = this->vec;
  this->vec = new T[this->rows*this->cols]{0};

  for (unsigned int r = 0; r < row; r++) {
    for (unsigned int c = 0; c < this->cols; c++) {
      this->set_element(r, c, old_vec[r * this->cols + c]);
    }
  }
  for (unsigned int c = 0; c < this->cols; c++) {
      this->set_element(row, c, 0);
  }
  for (unsigned int r = row; r < this->rows-1; r++) {
    for (unsigned int c = 0; c < this->cols; c++) {
      this->set_element(r+1, c, old_vec[r * this->cols + c]);
    }
  }
  delete[] old_vec;
}

template <class T>
void Matrix<T>::append_row(unsigned int row) {
  insert_row(row+1);
}

template <class T>
void Matrix<T>::remove_row(unsigned int row) {
  if (this->rows == 0 || this->cols == 0 || row >= this->rows) {
    throw std::out_of_range("Column cannot be removed: Index out of range");
  }
  this->rows--;
  T* old_vec = this->vec;

  if (this->rows == 0) {
    this->vec = new T[0];
  }
  else {
    this->vec = new T[this->rows*this->cols]{0};
  }

  for (unsigned int r = 0; r < row; r++) {
    for (unsigned int c = 0; c < this->cols; c++) {
      this->set_element(r, c, old_vec[r * this->cols + c]);
    }
  }
  for (unsigned int r = row+1; r < this->rows+1; r++) {
    for (unsigned int c = 0; c < this->cols; c++) {
      this->set_element(r-1, c, old_vec[r * this->cols + c]);
    }
  }
  delete[] old_vec;
}

template <class T>
void Matrix<T>::insert_col(unsigned int col) {
  if (this->rows == 0 || this->cols == 0 || col > this->cols) {
    throw std::out_of_range(
      "Cannot carry out column operation: Index is out of range"
    );
  }

  this->cols++;
  T* old_vec = this->vec;
  this->vec = new T[this->rows*this->cols]{0};

  for (unsigned int c = 0; c < col; c++) {
    for (unsigned int r = 0; r < this->rows; r++) {
      this->set_element(r, c, old_vec[r * (this->cols-1) + c]);
    }
  }
  for (unsigned int r = 0; r < this->rows; r++) {
      this->set_element(r, col, 0);
  }
  for (unsigned int c = col; c < this->cols-1; c++) {
    for (unsigned int r = 0; r < this->rows; r++) {
      this->set_element(r, c+1, old_vec[r * (this->cols-1) + c]);
    }
  }
  delete[] old_vec;
}

template <class T>
void Matrix<T>::append_col(unsigned int col) {
  insert_col(col+1);
}

template <class T>
void Matrix<T>::remove_col(unsigned int col) {
  if (this->rows == 0 || this->cols == 0 || col >= this->cols) {
    throw std::out_of_range("Column cannot be removed: Index out of range");
  }

  this->cols--;
  T* old_vec = this->vec;

  if (this->rows == 0) {
    this->vec = new T[0];
  }
  else {
    this->vec = new T[this->rows*this->cols]{0};
  }

  for (unsigned int r = 0; r < this->rows; r++) {
    for (unsigned int c = 0; c < col; c++) {
      this->set_element(r, c, old_vec[r * (this->cols+1) + c]);
    }
  }
  for (unsigned int r = 0; r < this->rows; r++) {
    for (unsigned int c = col+1; c < this->cols+1; c++) {
      this->set_element(r, c-1, old_vec[r * (this->cols+1) + c]);
    }
  }

  delete[] old_vec;
}

template <class T>
void Matrix<T>::reset() {
  int s = this->rows*this->cols;
  while (s--) {
    this->vec[s] = 0;
  }
}

template <class T>
void Matrix<T>::transpose() {
  Matrix<T> temp_m(this->cols, this->rows);

  for (unsigned int r = 0; r < this->rows; r++) {
    for (unsigned int c = 0; c < this->cols; c++) {
      temp_m.set_element(c, r, this->get_element(r, c));
    }
  }

  *this = temp_m;
}

template <class T>
void Matrix<T>::resize(unsigned int r, unsigned int c) {
  T* new_vec = new T[r*c]{0};

  this->rows = r;
  this->cols = c;

  delete[] this->vec;
  this->vec = new_vec;
}

template <class T>
Matrix<T> Matrix<T>::identity(unsigned int size) {
  Matrix<T> m(size);
  for (unsigned int r = 0; r < size; r++) {
    for (unsigned int c = 0; c < size; c++) {
      if (r == c) {
        m.set_element(r, c, 1);
      }
    }
  }
  return m;
}


#endif

