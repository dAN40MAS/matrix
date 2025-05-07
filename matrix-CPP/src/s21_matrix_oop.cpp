#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_{DEFAULTRAWS}, cols_{DEFAULTCOLS} {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range(
        "Incorrect input, arguments has to be greater than 0");
  }
  matrix_ = new double[rows_ * cols_]{};
}

S21Matrix::S21Matrix(int rows, int cols) : rows_{rows}, cols_{cols} {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range(
        "Incorrect input, arguments has to be greater than 0");
  }
  matrix_ = new double[rows_ * cols_]{};
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) = other(i, j);
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_{other.rows_}, cols_{other.cols_}, matrix_{other.matrix_} {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21Matrix tmp(other);
    rows_ = tmp.rows_;
    cols_ = tmp.cols_;
    delete[] matrix_;
    matrix_ = tmp.matrix_;
    tmp.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Incorrect input, different matrix dimensions");
  }
  S21Matrix temp_matrix{*this};
  temp_matrix.SumMatrix(other);
  return temp_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Incorrect input, different matrix dimensions");
  }
  S21Matrix temp_matrix{*this};
  temp_matrix.SubMatrix(other);
  return temp_matrix;
}

S21Matrix S21Matrix::operator*(double number) const {
  S21Matrix temp_matrix{*this};
  temp_matrix.MulNumber(number);
  return temp_matrix;
}

S21Matrix operator*(double number, const S21Matrix& other) {
  S21Matrix temp_matrix = other * number;
  return temp_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix temp_matrix{*this};
  temp_matrix.MulMatrix(other);
  return temp_matrix;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("index is out of range");
  }
  return matrix_[row * cols_ + col];
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::abs((*this)(i, j) - other(i, j)) > EPSILON) return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("different matrix dimensions");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("different matrix dimensions");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "Incorrect input, the number of columns of the first matrix is not "
        "equal to the number of rows of the second matrix ");
  }
  S21Matrix temp_matrix{rows_, other.cols_};
  for (int i = 0; i < temp_matrix.rows_; ++i) {
    for (int j = 0; j < temp_matrix.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        temp_matrix(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(temp_matrix);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix temp_matrix{cols_, rows_};
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      temp_matrix(j, i) = (*this)(i, j);
    }
  }
  return temp_matrix;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect input, the matrix is not square");
  }
  S21Matrix temp_matrix{*this};
  double determinant = 1.0;
  for (int j = 0; j < cols_; ++j) {
    double value_pivot = 0.0;
    int i_pivot = j;
    for (int i = j; i < rows_; ++i) {
      if (value_pivot < std::abs(temp_matrix(i, j))) {
        value_pivot = std::abs(temp_matrix(i, j));
        i_pivot = i;
      }
    }
    if (std::abs(temp_matrix(i_pivot, j)) - EPSILON <= 0.0) {
      determinant = 0.0;
      return determinant;
    }
    if (i_pivot != j) {
      temp_matrix.SwapRows(j, i_pivot);
      determinant *= -1.0;
    }
    determinant *= temp_matrix(j, j);
    for (int i2 = j + 1; i2 < rows_; ++i2) {
      double k = temp_matrix(i2, j) / temp_matrix(j, j);
      for (int j2 = j; j2 < cols_; ++j2) {
        temp_matrix(i2, j2) -= k * temp_matrix(j, j2);
      }
    }
  }
  return determinant;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect input, the matrix is not square");
  }
  S21Matrix complements_matrix{rows_, cols_};
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor_matrix = (*this).GetComplementaryMinor(i, j);
      double complement = minor_matrix.Determinant();
      if ((i + j) % 2 == 1) {
        complement *= -1.0;
      }
      complements_matrix(i, j) = complement;
    }
  }
  return complements_matrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect input, the matrix is not square");
  } else if (std::abs((*this).Determinant()) - EPSILON <= 0.0) {
    throw std::logic_error(
        "Incorrect input, no invertible matrix: determinant is 0");
  }
  S21Matrix temp_matrix(*this);
  S21Matrix inverse_matrix = GetIdentityMatrix(rows_);
  for (int j = 0; j < cols_; ++j) {
    double value_pivot = 0.0;
    int i_pivot = j;
    for (int i = j; i < rows_; ++i) {
      if (value_pivot < std::abs(temp_matrix(i, j))) {
        value_pivot = std::abs(temp_matrix(i, j));
        i_pivot = i;
      }
    }
    temp_matrix.SwapRows(j, i_pivot);
    inverse_matrix.SwapRows(j, i_pivot);
    for (int i = j + 1; i < rows_; ++i) {
      double k = temp_matrix(i, j) / temp_matrix(j, j);
      for (int j2 = 0; j2 < cols_; ++j2) {
        temp_matrix(i, j2) -= k * temp_matrix(j, j2);
        inverse_matrix(i, j2) -= k * inverse_matrix(j, j2);
      }
    }
    double k = temp_matrix(j, j);
    for (int j2 = cols_ - 1; j2 >= 0; --j2) {
      inverse_matrix(j, j2) /= k;
      temp_matrix(j, j2) /= k;
    }
  }
  for (int j = 0; j < cols_; ++j) {
    for (int i = 0; i < j; ++i) {
      double k = temp_matrix(i, j);
      for (int j2 = 0; j2 < cols_; ++j2) {
        temp_matrix(i, j2) -= k * temp_matrix(j, j2);
        inverse_matrix(i, j2) -= k * inverse_matrix(j, j2);
      }
    }
  }
  return inverse_matrix;
};

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int new_rows) {
  if (new_rows <= 0) {
    throw std::out_of_range("Incorrect input, the number of rows is below 1");
  }
  if (new_rows != rows_) {
    S21Matrix new_matrix{new_rows, cols_};
    int min_rows;
    if (rows_ > new_rows) {
      min_rows = new_rows;
    } else {
      min_rows = rows_;
    }
    for (int i = 0; i < min_rows; ++i) {
      for (int j = 0; j < cols_; ++j) {
        new_matrix(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(new_matrix);
  }
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols <= 0) {
    throw std::out_of_range(
        "Incorrect input, the number of columns is below 1");
  }
  if (new_cols != cols_) {
    S21Matrix new_matrix{rows_, new_cols};
    int min_cols;
    if (cols_ > new_cols) {
      min_cols = new_cols;
    } else {
      min_cols = cols_;
    }
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < min_cols; ++j) {
        new_matrix(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(new_matrix);
  }
}

void S21Matrix::SetRowsCols(int new_rows, int new_cols) {
  if (new_rows <= 0 || new_cols <= 0) {
    throw std::out_of_range(
        "Incorrect input, the number of rows or columns is below 1");
  }
  if (new_rows != rows_ || new_cols != cols_) {
    S21Matrix new_matrix{new_rows, new_cols};
    int min_rows;
    if (rows_ > new_rows) {
      min_rows = new_rows;
    } else {
      min_rows = rows_;
    }
    int min_cols;
    if (cols_ > new_cols) {
      min_cols = new_cols;
    } else {
      min_cols = cols_;
    }
    for (int i = 0; i < min_rows; ++i) {
      for (int j = 0; j < min_cols; ++j) {
        new_matrix(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(new_matrix);
  }
}
void S21Matrix::SwapRows(int row1, int row2) {
  if (row1 != row2) {
    for (int j = 0; j < cols_; ++j) {
      std::swap((*this)(row1, j), (*this)(row2, j));
    }
  }
}
S21Matrix S21Matrix::GetComplementaryMinor(int row, int col) {
  if (rows_ == 1) {
    throw std::logic_error(
        "Incorrect input, a 1-dimensional matrix has no minor");
  }
  S21Matrix minor_matrix{rows_ - 1, cols_ - 1};
  int i2;
  int j2;
  for (int i = 0; i < minor_matrix.rows_; ++i) {
    if (i < row) {
      i2 = i;
    } else {
      i2 = i + 1;
    }
    for (int j = 0; j < minor_matrix.cols_; j++) {
      if (j < col) {
        j2 = j;
      } else {
        j2 = j + 1;
      }
      minor_matrix(i, j) = (*this)(i2, j2);
    }
  }
  return minor_matrix;
}
S21Matrix S21Matrix::GetIdentityMatrix(int size) {
  S21Matrix identity_matrix{size, size};
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i == j) {
        identity_matrix(i, j) = 1.0;
      } else {
        identity_matrix(i, j) = 0.0;
      }
    }
  }
  return identity_matrix;
}
