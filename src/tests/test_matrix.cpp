#include "../s21_matrix_oop.h"
#include "gtest/gtest.h"

TEST(test_constructor, defualt_1) {
  S21Matrix mat;
  EXPECT_EQ(mat.getColumn(), 0);
  EXPECT_EQ(mat.getRow(), 0);
}

TEST(test_constructor, defualt_2) {
  EXPECT_THROW(S21Matrix mat(-1, 2), std::length_error);
  EXPECT_THROW(S21Matrix mat1(2, -1), std::length_error);
  EXPECT_THROW(S21Matrix mat2(-1, -1), std::length_error);
}

TEST(test_constructor, defualt_3) {
  S21Matrix mat(3, 5);
  EXPECT_EQ(mat(1, 2), 0);
  EXPECT_EQ(mat.getRow(), 3);
  EXPECT_EQ(mat.getColumn(), 5);
  EXPECT_THROW(mat(-1, 2), std::out_of_range);
  EXPECT_THROW(mat(3, 5), std::out_of_range);
}

TEST(test_constructor, defualt_4) {
  S21Matrix mat(5);
  EXPECT_EQ(mat(1, 2), 0);
  EXPECT_EQ(mat.getRow(), 5);
  EXPECT_EQ(mat.getColumn(), 5);
  EXPECT_THROW(mat(-1, 2), std::out_of_range);
  EXPECT_THROW(mat(6, 5), std::out_of_range);
}

TEST(test_constructor, copy_1) {
  S21Matrix mat(2, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix matCopy(mat);
  EXPECT_EQ(matCopy.getRow(), 2);
  EXPECT_EQ(matCopy.getColumn(), 3);
  EXPECT_EQ(mat == matCopy, true);
}

TEST(test_constructor, copy_2) {
  S21Matrix mat(4);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix matCopy(mat);
  EXPECT_EQ(matCopy.getRow(), 4);
  EXPECT_EQ(matCopy.getColumn(), 4);
  EXPECT_EQ(mat == matCopy, true);
}

TEST(test_constructor, copy_operator_1) {
  S21Matrix mat(7, 1);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix matCopy = mat;
  EXPECT_EQ(matCopy.getRow(), 7);
  EXPECT_EQ(matCopy.getColumn(), 1);
  EXPECT_EQ(mat == matCopy, true);
}

TEST(test_constructor, copy_operator_2) {
  S21Matrix mat0(1, 2);
  S21Matrix mat(5);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix matCopy(mat0);
  matCopy = mat;
  EXPECT_EQ(matCopy.getRow(), 5);
  EXPECT_EQ(matCopy.getColumn(), 5);
  EXPECT_EQ(mat == matCopy, true);
}

TEST(test_constructor, move_1) {
  S21Matrix mat(3, 2);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix matMove(std::move(mat));
  EXPECT_EQ(matMove.getRow(), 3);
  EXPECT_EQ(matMove.getColumn(), 2);
  EXPECT_EQ(mat.getRow(), 0);
  EXPECT_EQ(mat.getColumn(), 0);
}

TEST(test_constructor, move_2) {
  S21Matrix mat(4);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix matMove(std::move(mat));
  EXPECT_EQ(matMove.getRow(), 4);
  EXPECT_EQ(matMove.getColumn(), 4);
  EXPECT_EQ(mat.getRow(), 0);
  EXPECT_EQ(mat.getColumn(), 0);
}

TEST(test_constructor, move_operator_1) {
  S21Matrix mat(4);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix matMove;
  matMove = std::move(mat);
  EXPECT_EQ(matMove.getRow(), 4);
  EXPECT_EQ(matMove.getColumn(), 4);
  EXPECT_EQ(mat.getRow(), 0);
  EXPECT_EQ(mat.getColumn(), 0);
}

TEST(test_constructor, move_operator_2) {
  S21Matrix mat0(2, 2);
  S21Matrix mat(4);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix matMove(std::move(mat0));
  EXPECT_EQ(matMove.getRow(), 2);
  EXPECT_EQ(matMove.getColumn(), 2);
  EXPECT_EQ(mat0.getRow(), 0);
  EXPECT_EQ(mat0.getColumn(), 0);
  matMove = std::move(mat);
  EXPECT_EQ(matMove.getRow(), 4);
  EXPECT_EQ(matMove.getColumn(), 4);
  EXPECT_EQ(mat.getRow(), 2);
  EXPECT_EQ(mat.getColumn(), 2);
}

TEST(test_setter, set_row_1) {
  S21Matrix mat(7, 1);
  S21Matrix temp(7, 1);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      temp(i, j) = mat(i, j);
    }
  }
  mat.setRows(3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      EXPECT_NEAR(mat(i, j), temp(i, j), 1e-6);
    }
  }
  for (int i = temp.getRow(); i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      EXPECT_NEAR(mat(i, j), 0.0, 1e-6);
    }
  }
  EXPECT_EQ(mat.getRow(), 3);
  EXPECT_EQ(mat.getColumn(), 1);
}

TEST(test_setter, set_row_2) {
  S21Matrix mat(2, 4);
  S21Matrix temp(2, 4);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      temp(i, j) = mat(i, j);
    }
  }
  mat.setRows(5);
  for (int i = 0; i < temp.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      EXPECT_NEAR(mat(i, j), temp(i, j), 1e-6);
    }
  }
  for (int i = temp.getRow(); i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      EXPECT_NEAR(mat(i, j), 0.0, 1e-6);
    }
  }
  EXPECT_EQ(mat.getRow(), 5);
  EXPECT_EQ(mat.getColumn(), 4);
}

TEST(test_setter, set_row_3) {
  S21Matrix mat(7, 1);
  EXPECT_THROW(mat.setRows(-1), std::length_error);
  EXPECT_THROW(mat.setRows(0), std::length_error);
}

TEST(test_setter, set_column_1) {
  S21Matrix mat(7, 5);
  S21Matrix temp(7, 5);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      temp(i, j) = mat(i, j);
    }
  }
  mat.setColumns(3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      EXPECT_NEAR(mat(i, j), temp(i, j), 1e-6);
    }
  }
  EXPECT_EQ(mat.getRow(), 7);
  EXPECT_EQ(mat.getColumn(), 3);
}

TEST(test_setter, set_column_2) {
  S21Matrix mat(2, 2);
  S21Matrix temp(2, 2);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      temp(i, j) = mat(i, j);
    }
  }
  mat.setColumns(5);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < temp.getColumn(); j++) {
      EXPECT_EQ(temp(i, j), mat(i, j));
    }
  }
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = temp.getColumn(); j < mat.getColumn(); j++) {
      EXPECT_NEAR(mat(i, j), 0.0, 1e-6);
    }
  }
  EXPECT_EQ(mat.getRow(), 2);
  EXPECT_EQ(mat.getColumn(), 5);
}

TEST(test_setter, set_column_3) {
  S21Matrix mat(7, 1);
  EXPECT_THROW(mat.setColumns(-1), std::length_error);
  EXPECT_THROW(mat.setColumns(0), std::length_error);
}

TEST(test_functions_and_operators, eq_matrix_1) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = mat(i, j);
    }
  }
  EXPECT_EQ(mat.EqMatrix(mat2), true);
  EXPECT_EQ(mat == mat2, true);
  EXPECT_EQ(mat != mat2, false);
}

TEST(test_functions_and_operators, eq_matrix_2) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 5);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = mat(i, j);
    }
  }
  mat2(2, 4) = 1000;
  EXPECT_EQ(mat.EqMatrix(mat2), false);
  EXPECT_EQ(mat == mat2, false);
  EXPECT_EQ(mat != mat2, true);
}

TEST(test_functions_and_operators, eq_matrix_3) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = mat(i, j) + 1.0;
    }
  }
  EXPECT_EQ(mat.EqMatrix(mat2), false);
  EXPECT_EQ(mat == mat2, false);
  EXPECT_EQ(mat != mat2, true);
}

TEST(test_functions_and_operators, sum_matrix_1) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) + mat2(i, j);
    }
  }
  mat.SumMatrix(mat2);
  EXPECT_EQ(mat == res, true);
}

TEST(test_functions_and_operators, sum_matrix_2) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) + mat2(i, j);
    }
  }
  mat += mat2;
  EXPECT_EQ(mat == res, true);
}

TEST(test_functions_and_operators, sum_matrix_3) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) + mat2(i, j);
    }
  }
  S21Matrix mat3 = mat + mat2;
  EXPECT_EQ(mat3 == res, true);
}

TEST(test_functions_and_operators, sum_matrix_4) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 5);
  EXPECT_THROW(mat.SumMatrix(mat2), std::logic_error);
}

TEST(test_functions_and_operators, sub_matrix_1) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) - mat2(i, j);
    }
  }
  mat.SubMatrix(mat2);
  EXPECT_EQ(mat == res, true);
}

TEST(test_functions_and_operators, sub_matrix_2) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) - mat2(i, j);
    }
  }
  mat -= mat2;
  EXPECT_EQ(mat == res, true);
}

TEST(test_functions_and_operators, sub_matrix_3) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) - mat2(i, j);
    }
  }
  S21Matrix mat3 = mat - mat2;
  EXPECT_EQ(mat3 == res, true);
}

TEST(test_functions_and_operators, sub_matrix_4) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 5);
  EXPECT_THROW(mat.SubMatrix(mat2), std::logic_error);
}

TEST(test_functions_and_operators, mul_numb_matrix_1) {
  S21Matrix mat(3, 3);
  double num = 3.2;
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) * num;
    }
  }
  mat.MulNumber(num);
  EXPECT_EQ(mat == res, true);
}

TEST(test_functions_and_operators, mul_numb_matrix_2) {
  S21Matrix mat(3, 3);
  double num = 3.2;
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) * num;
    }
  }
  mat *= num;
  EXPECT_EQ(mat == res, true);
}

TEST(test_functions_and_operators, mul_numb_matrix_3) {
  S21Matrix mat(3, 3);
  double num = 3.2;
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) * num;
    }
  }
  S21Matrix mat2 = mat * num;
  EXPECT_EQ(mat2 == res, true);
}

TEST(test_functions_and_operators, mul_numb_matrix_4) {
  S21Matrix mat(3, 3);
  double num = 3.2;
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      res(i, j) = mat(i, j) * num;
    }
  }
  S21Matrix mat2 = num * mat;
  EXPECT_EQ(mat2 == res, true);
}

TEST(test_functions_and_operators, mul_matrix_1) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
      mat2(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix res(3, 3);
  for (int i = 0; i < res.getRow(); i++) {
    for (int j = 0; j < res.getColumn(); j++) {
      for (int k = 0; k < mat.getColumn(); k++) {
        res(i, j) += mat(i, k) * mat2(k, j);
      }
    }
  }
  mat.MulMatrix(mat2);
  EXPECT_EQ(mat == res, true);
}

TEST(test_functions_and_operators, mul_matrix_2) {
  S21Matrix mat(3, 2);
  S21Matrix mat2(2, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  for (int i = 0; i < mat2.getRow(); i++) {
    for (int j = 0; j < mat2.getColumn(); j++) {
      mat2(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix res(3, 3);
  for (int i = 0; i < res.getRow(); i++) {
    for (int j = 0; j < res.getColumn(); j++) {
      for (int k = 0; k < mat.getColumn(); k++) {
        res(i, j) += mat(i, k) * mat2(k, j);
      }
    }
  }
  mat.MulMatrix(mat2);
  EXPECT_EQ(mat == res, true);
  EXPECT_EQ(mat.getRow(), 3);
  EXPECT_EQ(mat.getColumn(), 3);
}

TEST(test_functions_and_operators, mul_matrix_3) {
  S21Matrix mat(5, 4);
  S21Matrix mat2(4, 6);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  for (int i = 0; i < mat2.getRow(); i++) {
    for (int j = 0; j < mat2.getColumn(); j++) {
      mat2(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix res(5, 6);
  for (int i = 0; i < res.getRow(); i++) {
    for (int j = 0; j < res.getColumn(); j++) {
      for (int k = 0; k < mat.getColumn(); k++) {
        res(i, j) += mat(i, k) * mat2(k, j);
      }
    }
  }
  mat.MulMatrix(mat2);
  EXPECT_EQ(mat == res, true);
  EXPECT_EQ(mat.getRow(), 5);
  EXPECT_EQ(mat.getColumn(), 6);
}

TEST(test_functions_and_operators, mul_matrix_4) {
  S21Matrix mat(5, 4);
  S21Matrix mat2(4, 6);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  for (int i = 0; i < mat2.getRow(); i++) {
    for (int j = 0; j < mat2.getColumn(); j++) {
      mat2(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix res(5, 6);
  for (int i = 0; i < res.getRow(); i++) {
    for (int j = 0; j < res.getColumn(); j++) {
      for (int k = 0; k < mat.getColumn(); k++) {
        res(i, j) += mat(i, k) * mat2(k, j);
      }
    }
  }
  mat *= mat2;
  EXPECT_EQ(mat == res, true);
  EXPECT_EQ(mat.getRow(), 5);
  EXPECT_EQ(mat.getColumn(), 6);
}

TEST(test_functions_and_operators, mul_matrix_5) {
  S21Matrix mat(5, 4);
  S21Matrix mat2(4, 6);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  for (int i = 0; i < mat2.getRow(); i++) {
    for (int j = 0; j < mat2.getColumn(); j++) {
      mat2(i, j) = rand() % 100 - 50;
    }
  }
  S21Matrix res(5, 6);
  for (int i = 0; i < res.getRow(); i++) {
    for (int j = 0; j < res.getColumn(); j++) {
      for (int k = 0; k < mat.getColumn(); k++) {
        res(i, j) += mat(i, k) * mat2(k, j);
      }
    }
  }
  S21Matrix mat3 = mat * mat2;
  EXPECT_EQ(mat3 == res, true);
  EXPECT_EQ(mat3.getRow(), 5);
  EXPECT_EQ(mat3.getColumn(), 6);
}

TEST(test_functions_and_operators, mul_matrix_6) {
  S21Matrix mat(1, 2);
  S21Matrix mat2(3, 4);
  EXPECT_THROW(mat.MulMatrix(mat2), std::logic_error);
  EXPECT_THROW(mat *= mat2, std::logic_error);
  EXPECT_THROW(mat * mat2, std::logic_error);
}

TEST(test_functions_and_operators, transpose_matrix_1) {
  S21Matrix mat(3, 3);
  S21Matrix res(3, 3);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      res(i, j) = mat(j, i);
    }
  }
  S21Matrix mat3 = mat.Transpose();
  EXPECT_EQ(mat3 == res, true);
}

TEST(test_functions_and_operators, transpose_matrix_2) {
  S21Matrix mat(1, 3);
  S21Matrix res(3, 1);
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = rand() % 100 - 50;
    }
  }
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      res(j, i) = mat(i, j);
    }
  }
  S21Matrix mat3 = mat.Transpose();
  EXPECT_EQ(mat3 == res, true);
}

TEST(test_functions_and_operators, determinant_1) {
  S21Matrix mat(3, 3);
  double count = 1.0;
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = count++;
    }
  }
  EXPECT_EQ(mat.Determinant(), 0.0);
}

TEST(test_functions_and_operators, determinant_2) {
  S21Matrix mat(1, 3);
  EXPECT_THROW(mat.Determinant(), std::logic_error);
}

TEST(test_functions_and_operators, determinant_3) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 2.0;
  mat(0, 1) = 3.0;
  mat(0, 2) = 1.0;
  mat(1, 0) = 7.0;
  mat(1, 1) = 4.0;
  mat(1, 2) = 1.0;
  mat(2, 0) = 9.0;
  mat(2, 1) = -2.0;
  mat(2, 2) = 1.0;
  EXPECT_NEAR(mat.Determinant(), -32.0, 1.0e-6);
}

TEST(test_functions_and_operators, determinant_4) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 3.0;
  mat(0, 1) = 2.0;
  mat(1, 0) = 8.0;
  mat(1, 1) = 7.0;
  EXPECT_NEAR(mat.Determinant(), 5.0, 1.0e-6);
}

TEST(test_functions_and_operators, determinant_5) {
  S21Matrix mat(1, 1);
  mat(0, 0) = 1488;
  EXPECT_NEAR(mat.Determinant(), 1488.0, 1.0e-6);
}

TEST(test_functions_and_operators, calc_comp_1) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 7.0;
  mat(0, 1) = 8.0;
  mat(0, 2) = 9.0;
  mat(1, 0) = 4.0;
  mat(1, 1) = 5.0;
  mat(1, 2) = 6.0;
  mat(2, 0) = 2.0;
  mat(2, 1) = 3.0;
  mat(2, 2) = 1.0;

  S21Matrix res(3, 3);
  res(0, 0) = -13.0;
  res(0, 1) = 8.0;
  res(0, 2) = 2.0;
  res(1, 0) = 19.0;
  res(1, 1) = -11.0;
  res(1, 2) = -5.0;
  res(2, 0) = 3.0;
  res(2, 1) = -6.0;
  res(2, 2) = 3.0;
  EXPECT_EQ(mat.CalcComplements() == res, true);
}

TEST(test_functions_and_operators, calc_comp_2) {
  S21Matrix mat(1, 3);
  EXPECT_THROW(mat.CalcComplements(), std::logic_error);
}

TEST(test_functions_and_operators, calc_comp_3) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1.0;
  mat(0, 1) = 4.0;
  mat(1, 0) = 8.0;
  mat(1, 1) = 8.0;

  S21Matrix res(2, 2);
  res(0, 0) = 8.0;
  res(0, 1) = -8.0;
  res(1, 0) = -4.0;
  res(1, 1) = 1.0;
  EXPECT_EQ(mat.CalcComplements() == res, true);
}

TEST(test_functions_and_operators, calc_comp_4) {
  S21Matrix mat(1, 1);
  mat(0, 0) = 34.0;

  S21Matrix res(1, 1);
  res(0, 0) = 34.0;
  EXPECT_EQ(mat.CalcComplements() == res, true);
}

TEST(test_functions_and_operators, inverse_matrix_1) {
  S21Matrix mat(1, 3);
  EXPECT_THROW(mat.InverseMatrix(), std::logic_error);
}

TEST(test_functions_and_operators, inverse_matrix_2) {
  S21Matrix mat(3, 3);
  double count = 1.0;
  for (int i = 0; i < mat.getRow(); i++) {
    for (int j = 0; j < mat.getColumn(); j++) {
      mat(i, j) = count++;
    }
  }
  EXPECT_THROW(mat.InverseMatrix(), std::logic_error);
}

TEST(test_functions_and_operators, inverse_matrix_3) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 2.8;
  mat(0, 1) = 1.3;
  mat(0, 2) = 7.01;
  mat(1, 0) = -1.03;
  mat(1, 1) = -2.3;
  mat(1, 2) = 3.01;
  mat(2, 0) = 0.0;
  mat(2, 1) = -3.0;
  mat(2, 2) = 2.0;

  S21Matrix res(3, 3);
  res(0, 0) = 44300.0 / 367429.0;
  res(0, 1) = -236300.0 / 367429.0;
  res(0, 2) = 200360.0 / 367429.0;
  res(1, 0) = 20600.0 / 367429.0;
  res(1, 1) = 56000.0 / 367429.0;
  res(1, 2) = -156483.0 / 367429.0;
  res(2, 0) = 30900.0 / 367429.0;
  res(2, 1) = 84000.0 / 367429.0;
  res(2, 2) = -51010.0 / 367429.0;
  EXPECT_EQ(mat.InverseMatrix() == res, true);
}

TEST(test_functions_and_operators, inverse_matrix_4) {
  S21Matrix mat(1, 1);
  mat(0, 0) = 1488.0;

  S21Matrix res(1, 1);
  res(0, 0) = 1.0 / 1488.0;
  EXPECT_EQ(mat.InverseMatrix() == res, true);
}

TEST(test_functions_and_operators, inverse_matrix_5) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1337.0;
  mat(0, 1) = 420.0;
  mat(1, 0) = 1488.0;
  mat(1, 1) = 228.0;

  S21Matrix res(2, 2);
  res(0, 0) = -19.0 / 26677.0;
  res(0, 1) = 5.0 / 3811.0;
  res(1, 0) = 124.0 / 26677.0;
  res(1, 1) = -191.0 / 45732.0;
  EXPECT_EQ(mat.InverseMatrix() == res, true);
}