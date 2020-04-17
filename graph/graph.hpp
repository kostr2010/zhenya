#pragma once

#include "../matrix/matrix.hpp"

#include <set>
#include <vector>

std::set<int> GetConnected(const MatrixSym& routes) {
  std::size_t   size = routes.GetSize();
  std::set<int> connected{};
  int           i{}, j{};

  for (i = 1; i <= size; i++) {
    for (j = 1; j <= size; j++) {
      if (routes(i, j) != 0) {
        connected.insert(i);
        break;
      }
    }
  }

  return connected;
}

void Dijkstra_(int origin, int current, const MatrixSym& routes, std::set<int> connected_joints,
               MatrixSym& distances) {

  connected_joints.erase(current);

  if (current == 0)
    return;

  for (const auto elem : connected_joints) {
    int route_cur_elem      = routes(current, elem);
    int distance_origin_cur = distances(origin, current);

    if (route_cur_elem != 0 && distances(origin, elem) > distance_origin_cur + route_cur_elem)
      distances(origin, elem) = distance_origin_cur + route_cur_elem;
  }

  for (const auto elem : connected_joints)
    Dijkstra_(origin, elem, routes, connected_joints, distances);
}

void Dijkstra(int origin, const MatrixSym& routes, std::set<int> connected_joints,
              MatrixSym& distances) {
  Dijkstra_(origin, origin, routes, connected_joints, distances);
}

MatrixSym GetDistances(const MatrixSym& routes, std::set<int> connected_joints) {
  MatrixSym distances{routes.GetSize(), 1000};

  for (const auto index : connected_joints) {
    distances(index, index) = 0;

    Dijkstra(index, routes, connected_joints, distances);
  }

  return distances;
}

int GetPartialSum(MatrixSym& distances, std::size_t str, std::size_t col,
                  std::set<int> available_col, std::set<int> available_str) {
  available_col.erase(col);
  available_str.erase(str);

  if (available_col.size() == 1 && available_str.size() == 1)
    return distances(str, col);

  int min_res = 1e6; // big number

  for (int str_new : available_str) {
    for (int col_new : available_col) {
      if (col_new == str_new)
        continue;

      int res = GetPartialSum(distances, str_new, col_new, available_col, available_str);

      if (res < min_res)
        min_res = res;
    }
  }

  return distances(str, col) + min_res;
}

int GetShortestByPass(MatrixSym& routes) {
  std::set<int> connected_joints = GetConnected(routes);

  MatrixSym distances = GetDistances(routes, connected_joints);

  return GetPartialSum(distances, 0, 0, connected_joints, connected_joints);
}