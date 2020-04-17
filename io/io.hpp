#pragma once

#include "../matrix/matrix.hpp"
#include <cassert>
#include <fstream>

MatrixSym ReadMatrix(const char* path) {
  std::ifstream input{path, std::ios_base::in};
  std::size_t   size{};

  assert(input >> size);

  MatrixSym routes = MatrixSym{size};

  int    str{}, col{};
  double val{};

  while (input >> str >> col >> val) {
    assert(str <= size && col <= size && str > 0 && col > 0);

    routes(str, col) = val;
  }

  return routes;
}