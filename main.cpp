#include "./graph/graph.hpp"
#include "./io/io.hpp"
#include "./matrix/matrix.hpp"

#include <cassert>
#include <fstream>

int main() {
  MatrixSym routes = ReadMatrix("./input.txt");

  std::cout << "> length of the shortest bypass = " << GetShortestByPass(routes) << std::endl;

  return 0;
}
