#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_
#include <math.h>
#include <stdlib.h>

#include <cstring>
#include <iostream>
#include <vector>

/*Вспомогательный класс
используется для перевода
вектора в матрицу и обратно
в классе Spiner*/

#define EPS 1e-7

class S21Matrix {
 private:
  int rows_, columns_;
  double** matrix_;

 public:
  //  Methods for filling matrix

  double Transfer(double value) {
    return 1.0 / (1.0 + exp(-value));
  }

  static double GenerateRandomNumber(double min, double max) {
    double random = (double) rand() / RAND_MAX;
    return min + random * (max - min);
  }
  void FillMatrix(bool random = false) {
    int k = 1;
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->columns_; j++)
        matrix_[i][j] = random ?
          GenerateRandomNumber(-1.00, 1.00) :
          k++;
  }
  void FillMatrix(double num) {
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->columns_; j++) this->matrix_[i][j] = num;
  }
  void SetValues(const std::vector<double>& num_array) {
    int k = 0;
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->columns_; j++)
        this->matrix_[i][j] = num_array[k++];
  }
  void TransferMatrix() {
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < columns_; ++j)
        matrix_[i][j] = Transfer(matrix_[i][j]);
  }
  void OutputMatrix() {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < columns_; ++j) {
        std::cout << matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  //  Constructors and destructor

  S21Matrix() : S21Matrix(3, 3) { ; }

  S21Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
    if (rows <= 0 || columns <= 0) throw std::out_of_range("Out of range");
    this->matrix_ = new double*[rows];
    for (int i = 0; i < rows; i++) {
      this->matrix_[i] = new double[columns]();
    }
  }

  S21Matrix(const S21Matrix& other) : S21Matrix(other.rows_, other.columns_) {
    this->SetEqualValues_(other);
  }

  S21Matrix(S21Matrix&& other)
      : rows_(other.rows_), columns_(other.columns_), matrix_(other.matrix_) {
    other.matrix_ = nullptr;
  }

  ~S21Matrix() { this->RemoveMatrix_(); }

  //  Operators overloads

  void operator=(const S21Matrix& other) {
    if (IsNull_(*this))
      this->CopyConstructor_(other);
    else
      this->SetEqualValues_(other);
  }

  void operator=(S21Matrix&& other) {
    this->RemoveMatrix_();
    rows_ = other.rows_;
    columns_ = other.columns_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
  }

  void operator-=(const S21Matrix& other) { this->SubMatrix(other); }

  void operator+=(const S21Matrix& other) { this->SumMatrix(other); }

  S21Matrix operator-(const S21Matrix& other) {
    S21Matrix result(*this);
    result.SubMatrix(other);
    return result;
  }

  S21Matrix operator+(const S21Matrix& other) {
    S21Matrix result(*this);
    result.SumMatrix(other);
    return result;
  }

  void operator*=(const S21Matrix& other) { this->MulMatrix(other); }

  void operator*=(double num) { this->MulNumber(num); }

  S21Matrix operator*(const S21Matrix& other) {
    S21Matrix result(*this);
    result.MulMatrix(other);
    return result;
  }

  S21Matrix operator*(double num) {
    S21Matrix result(*this);
    result.MulNumber(num);
    return result;
  }

  bool operator==(const S21Matrix& other) { return this->EqMatrix(other); }

  bool operator!=(const S21Matrix& other) { return !(this->EqMatrix(other)); }

  double& operator()(int i, int j) {
    if (i >= this->rows_ || j >= this->columns_ || i < 0 || j < 0)
      throw std::out_of_range("Out of range");
    return this->matrix_[i][j];
  }

  // Main methods

  void SetRows(int new_rows) {
    if (new_rows <= 0) throw std::out_of_range("Out of range");
    if (new_rows != this->rows_) {
      int rows_iter = (this->rows_ < new_rows) ? this->rows_ : new_rows;
      S21Matrix tmp(new_rows, this->columns_);
      for (int i = 0; i < rows_iter; i++)
        for (int j = 0; j < this->columns_; j++)
          tmp.matrix_[i][j] = this->matrix_[i][j];
      this->RemoveMatrix_();
      this->matrix_ = tmp.matrix_;
      this->rows_ = new_rows;
      tmp.matrix_ = nullptr;
    }
  }

  void SetColumns(int new_cols) {
    if (new_cols <= 0) throw std::out_of_range("Out of range");
    if (new_cols != this->columns_) {
      int cols_iter = (this->columns_ < new_cols) ? this->columns_ : new_cols;
      S21Matrix tmp(this->rows_, new_cols);
      for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < cols_iter; j++)
          tmp.matrix_[i][j] = this->matrix_[i][j];
      this->RemoveMatrix_();
      this->matrix_ = tmp.matrix_;
      this->columns_ = new_cols;
      tmp.matrix_ = nullptr;
    }
  }

  void SetSize(int new_rows, int new_cols) {
    this->SetRows(new_rows), this->SetColumns(new_cols);
  }

  int GetRows() {
    if (IsNull_(*this)) throw std::out_of_range("Out of range");
    return this->rows_;
  }

  int GetCols() {
    if (IsNull_(*this)) throw std::out_of_range("Out of range");
    return this->columns_;
  }

  bool EqMatrix(const S21Matrix& other) {
    bool eq_result = true;
    if (!IsNull_(*this, other) && IsRowsAndColsEq_(*this, other)) {
      for (int i = 0; i < this->rows_ && eq_result; i++)
        for (int j = 0; j < this->columns_ && eq_result; j++)
          if (this->matrix_[i][j] != other.matrix_[i][j]) eq_result = false;
    } else {
      eq_result = false;
    }
    return eq_result;
  }

  void SumMatrix(const S21Matrix& other) {
    if (IsNull_(*this, other) || !IsRowsAndColsEq_(*this, other))
      throw std::out_of_range("Out of range");
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->columns_; j++)
        this->matrix_[i][j] += other.matrix_[i][j];
  }

  void SubMatrix(const S21Matrix& other) {
    if (IsNull_(*this, other) || !IsRowsAndColsEq_(*this, other))
      throw std::out_of_range("Out of range");
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->columns_; j++)
        this->matrix_[i][j] -= other.matrix_[i][j];
  }

  void MulNumber(const double num) {
    if (!IsNull_(*this)) {
      for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++) this->matrix_[i][j] *= num;
    }
  }

  S21Matrix MulMatrix(const S21Matrix& other) {
    if (IsNull_(*this, other) || this->columns_ != other.rows_)
      throw std::out_of_range("Out of range");
    S21Matrix res_matrix(this->rows_, other.columns_);
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < other.columns_; j++)
        for (int k = 0; k < this->columns_; k++)
          res_matrix.matrix_[i][j] +=
              this->matrix_[i][k] * other.matrix_[k][j];
    return res_matrix;
  }

  S21Matrix Transpose() {
    S21Matrix res_matrix(this->columns_, this->rows_);
    if (!IsNull_(*this, res_matrix)) {
      for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
          res_matrix.matrix_[j][i] = this->matrix_[i][j];
    }
    return res_matrix;
  }

  static std::vector<double> MatrixToVector(const S21Matrix& matrix) {
    std::vector<double> vector(matrix.columns_ * matrix.rows_);
    auto it = vector.begin();
    for (int i = 0; i < matrix.rows_; ++i) {
      for (int j = 0; j < matrix.columns_; ++j) {
        *it = matrix.matrix_[i][j];
        ++it;
      }
    }
    return vector;
  }

  static S21Matrix VectorToMatrix(const std::vector<double>& other) {
    S21Matrix matrix(other.size() / 3, 3);
    auto it = other.begin();
    for (int i = 0; i < matrix.rows_; ++i)
      for (int j = 0; j < matrix.columns_; ++j) matrix.matrix_[i][j] = *(it++);
    return matrix;
  }

  // Internal methods
 private:
  bool IsSquared_() { return this->rows_ == this->columns_ ? true : false; }

  void SetEqualValues_(const S21Matrix& other) {
    this->SetSize(other.rows_, other.columns_);
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->columns_; j++)
        this->matrix_[i][j] = other.matrix_[i][j];
  }

  bool IsRowsAndColsEq_(const S21Matrix& matrix1, const S21Matrix& matrix2) {
    return ((matrix1.columns_ == matrix2.columns_) &&
            (matrix1.rows_ == matrix2.rows_))
               ? true
               : false;
  }

  bool IsNull_(const S21Matrix& matrix1, const S21Matrix& matrix2) {
    return matrix1.matrix_ != nullptr && matrix2.matrix_ != nullptr ? false
                                                                    : true;
  }

  bool IsNull_(const S21Matrix& matrix) {
    return matrix.matrix_ != nullptr ? false : true;
  }

  void CopyConstructor_(const S21Matrix& other) {
    S21Matrix tmp(other);
    this->rows_ = tmp.rows_;
    this->columns_ = tmp.columns_;
    this->matrix_ = tmp.matrix_;
    tmp.matrix_ = nullptr;
  }

  void RemoveMatrix_() {
    if (!IsNull_(*this)) {
      for (int i = 0; i < this->rows_; i++) delete[](this->matrix_[i]);
      delete[](this->matrix_);
    }
  }
};
#endif  // SRC_S21_MATRIX_H_
