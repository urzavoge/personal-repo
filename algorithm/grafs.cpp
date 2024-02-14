#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using std::cin, std::cout, std::vector, std::string, std::min, std::queue;

struct Graph {
  int num_vertex;
  const int kMax = std::numeric_limits<int>::max();

  vector<vector<int>> graph;
  vector<bool> used;
  vector<int> u;
  vector<int> v;
  vector<int> prev;
  vector<int> minv;
  vector<int> way;


  Graph() = default;
  void Build();
  void Solve();
};

void Graph::Build() {
  cin >> num_vertex;
  graph.resize(num_vertex + 1, vector<int>(num_vertex + 1, 0));
  used.resize(num_vertex + 1, false);
  prev.resize(num_vertex + 1, 0);
  minv.resize(num_vertex + 1, kMax);
  v.resize(num_vertex + 1, 0);
  u.resize(num_vertex + 1, 0);
  way.resize(num_vertex + 1, 0);

  int cap;
  for (int i = 1; i <= num_vertex; ++i) {
    for (int j = 1; j <= num_vertex; ++j) {
      cin >> cap;
      graph[i][j] = cap;
    }
  }
}

void Graph::Solve() {
  int level = 0;
  int column, line, delta, next, curr;
  for (int i = 1; i <= num_vertex; ++i) {
    prev[0] = i;
    column = 0;
    used.resize(num_vertex + 1, false);
    minv.resize(num_vertex + 1, kMax);
    do {
      used[column] = true;
      line = prev[column];
      delta = kMax;
      for (int j = 1; j <= num_vertex; ++j) {
        if (!used[j]) {
          curr = graph[line][j] - u[line] - v[j];
          if (curr < minv[j]) minv[j] = curr; way[j] = column;
          if (minv[j] < delta) delta = minv[j]; next = j;
        }
      }
      for (int j = 0; j <= num_vertex; ++j) {
        if (used[j]) {
          u[prev[j]] += delta;
          v[j] -= delta;
        } else {
          minv[j] -= delta;
        }
      }
      column = next;
    } while (prev[column] != 0);
    do {
      next = way[column];
      prev[column] = prev[next];
      column = next;
    } while (column != 0);
  }
  cout << -v[0] << '\n';
  for (int j = 1; j <= num_vertex; ++j) {
    cout << prev[j] << " " << j << '\n';
  }
}


int main() {
  Graph work = Graph();
  work.Build();
  work.Solve();
  return 0;
}