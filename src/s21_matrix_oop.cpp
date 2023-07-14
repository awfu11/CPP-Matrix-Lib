#include "s21_matrix_oop.hpp"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int size) : rows_(size), cols_(size) {
  if (size <= 0) {
    throw std::length_error("Array size can't be equal or less than zero.");
  }
  allocate();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::length_error("Array size can't be equal or less than zero.");
  }
  allocate();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
  }
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    clear();

    rows_ = other.rows_;
    cols_ = other.cols_;
    allocate();
    for (int i = 0; i < rows_; i++) {
      std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
    }
  }
  return *this;
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  std::swap(matrix_, other.matrix_);
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    std::swap(cols_, other.cols_);
    std::swap(rows_, other.rows_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    clear();
  }
}

void S21Matrix::allocate() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

void S21Matrix::clear() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

int S21Matrix::getRow() const noexcept { return rows_; }

int S21Matrix::getColumn() const noexcept { return cols_; }

void S21Matrix::setRows(const int new_row) {
  if (new_row <= 0) {
    throw std::length_error("Array size can't be equal or less than zero.");
  }
  S21Matrix temp(new_row, cols_);
  for (int i = 0; i < (new_row <= rows_ ? new_row : rows_); i++) {
    std::copy(matrix_[i], matrix_[i] + cols_, temp.matrix_[i]);
  }
  *this = std::move(temp);
}

void S21Matrix::setColumns(const int new_col) {
  if (new_col <= 0) {
    throw std::length_error("Array size can't be equal or less than zero.");
  }
  S21Matrix temp(rows_, new_col);
  for (int i = 0; i < rows_; i++) {
    std::copy(matrix_[i], matrix_[i] + (new_col <= cols_ ? new_col : cols_),
              temp.matrix_[i]);
  }
  *this = std::move(temp);
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1.0e-6) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Different matrix dimensions.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.");
  }
  S21Matrix temp(rows_, other.cols_);
  for (int i = 0; i < temp.rows_; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(temp);
}

S21Matrix S21Matrix::Transpose() const noexcept{
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

void S21Matrix::Minor(const S21Matrix& arr, int row, int column) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      int skip_row = (i >= row) ? 1 : 0;
      int skip_column = (j >= column) ? 1 : 0;
      matrix_[i][j] = arr.matrix_[i + skip_row][j + skip_column];
    }
  }
}

double S21Matrix::Det() const {
  if (rows_ == 1) {
    return matrix_[0][0];
  }
  double det = 0.0;
  S21Matrix temp(rows_ - 1, cols_ - 1);
  for (int i = 0; i < cols_; i++) {
    temp.Minor(*this, 0, i);
    det += (!(i % 2) ? 1 : -1) * matrix_[0][i] * temp.Det();
  }
  return det;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not square.");
  }
  return Det();
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not square.");
  }

  S21Matrix result(rows_, cols_);
  S21Matrix temp(rows_ != 1 ? (rows_ - 1) : 1);
  double det = 1.0;
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      if (rows_ != 1) {
        temp.Minor(*this, i, j);
        det = temp.Det();
      } else {
        det = (*this)(0, 0);
      }
      result.matrix_[i][j] = (!((i + j) % 2) ? 1 : -1) * det;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not square.");
  }
  double det = (*this).Determinant();
  if (fabs(det) < 1.0e-6) {
    throw std::logic_error("The determinant can't be zero.");
  }

  if (rows_ == 1) {
    S21Matrix result(rows_);
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
    return result;
  }
  S21Matrix result = (*this).CalcComplements().Transpose();
  return result *= (1.0 / det);
}

double& S21Matrix::operator()(const int row, const int column) const {
  if ((row < 0 || column < 0) || (row >= rows_ || column >= cols_)) {
    throw std::out_of_range("Index is outside the matrix.");
  }
  return matrix_[row][column];
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix& other) const noexcept {
  return !EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) noexcept {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(const S21Matrix& other, const double num) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}
