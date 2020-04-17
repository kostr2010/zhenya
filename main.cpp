#include "./graph/graph.hpp"
#include "./io/io.hpp"
#include "./matrix/matrix.hpp"

#include <cassert>
#include <fstream>

std::ostream& operator<<(std::ostream& os, std::set<int>& set) {
  for (const auto& elem : set)
    os << elem << " ";

  return os;
}

int main() {
  MatrixSym routes = ReadMatrix("./input.txt");

  std::cout << "> length of the shortest bypass = " << GetShortestByPass(routes) << std::endl;

  return 0;
}
