#pragma once

#include <cstring>
#include <iomanip>
#include <iostream>
#include <new>

#include "../utils/log.hpp"

class MatrixSym {
public:
  MatrixSym(std::size_t size, int init_value = 0) {
    size_ = size;
    buf_  = new int[(size + 1) * size / 2]{};

    if (init_value != 0) {
      for (int i = 0; i < size * (size + 1) / 2; i++)
        buf_[i] = init_value;
    }

    LOG_LVL_MATRIX_INIT();
  }

  MatrixSym(const MatrixSym& right) {
    size_ = right.GetSize();
    buf_  = new int[size_];

    memcpy(buf_, right.buf_, size_);

    LOG_LVL_MATRIX_INIT();
  }

  MatrixSym(MatrixSym&& right) {
    size_ = right.size_;
    buf_  = right.buf_;

    right.buf_ = nullptr;

    LOG_LVL_MATRIX_INIT();
  }

  ~MatrixSym() {
    LOG_LVL_MATRIX_ROUTINE("matrix destroyed");

    delete[] buf_;
  }

  MatrixSym& operator=(const MatrixSym& right) {
    delete[] buf_;

    size_ = right.size_;
    buf_  = new int[size_];

    memcpy(buf_, right.buf_, size_);

    return *this;
  }

  // not safe!
  int& operator()(std::size_t str, std::size_t col) {
    if (str < col)
      std::swap(str, col);

    LOG_LVL_MATRIX_ROUTINE("element {" << str << ", " << col << "} accessed via "
                                       << __PRETTY_FUNCTION__);

    return buf_[str * (str - 1) / 2 + (col - 1)];
  }

  // not safe!
  int operator()(std::size_t str, std::size_t col) const {
    if (str < col)
      std::swap(str, col);

    LOG_LVL_MATRIX_ROUTINE("element {" << str << ", " << col << "} accessed via "
                                       << __PRETTY_FUNCTION__);

    return buf_[str * (str - 1) / 2 + (col - 1)];
  }

  // safe
  inline int* At(std::size_t str, std::size_t col) {
    if (str < col)
      std::swap(str, col);

    if (str > size_) {
      LOG_LVL_MATRIX_FAILURE("entered parameters {" << str << ", " << col
                                                    << "} are out or range for matrix {" << size_
                                                    << "}");
      return nullptr;
    } else {
      LOG_LVL_MATRIX_ROUTINE("element {" << str << ", " << col << "} accessed via "
                                         << __PRETTY_FUNCTION__);

      return buf_ + str * (str - 1) / 2 + (col - 1);
    }
  }

  inline std::size_t GetSize() const {
    return size_;
  }

  friend std::ostream& operator<<(std::ostream& stream, MatrixSym& matrix) {
    std::size_t size = matrix.GetSize();

    for (int i = 1; i <= size; i++) {
      for (int j = 1; j <= size; j++)
        stream << std::setw(5) << std::left << std::setprecision(3) << matrix(i, j) << " ";

      stream << std::endl;
    }

    return stream;
  }

private:
  std::size_t size_;
  int*        buf_;
};
