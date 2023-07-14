#ifndef _S21_MATRIX_OOP_H_
#define _S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void allocate();
  void clear();
  void Minor(const S21Matrix& arr, int row, int column) noexcept;
  double Det() const;

 public:
  S21Matrix();
  explicit S21Matrix(int size);
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int getRow() const noexcept;
  int getColumn() const noexcept;
  void setRows(const int new_row);
  void setColumns(const int new_col);

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const noexcept;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;

  double& operator()(const int row, const int col) const;
  bool operator==(const S21Matrix& other) const noexcept;
  bool operator!=(const S21Matrix& other) const noexcept;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const double num) noexcept;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix& operator*=(const S21Matrix& other);
  friend S21Matrix operator*(const double num, const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& other, const double num);
};

#endif  // _S21_MATRIX_OOP_H_
