#include <iostream>

#include <vector>

#include <algorithm>

using std::vector, std::cin, std::cout, std::min;
const int kInf = 1000 * 1000 * 1000;

struct Node {
  int first, pos_first;
  int second, pos_second;
  Node() = default;
  Node(int a, int ia, int b, int ib)
      : first(a), pos_first(ia), second(b), pos_second(ib) {}
};

Node Min(Node x, Node y) {
  int a, b, ia, ib;
  if (x.first == y.first) {
    if (x.pos_first != y.pos_first) {
      a = x.first;
      ia = x.pos_first;
      b = y.first;
      ib = y.pos_first;
    } else {
      a = x.first;
      ia = x.pos_first;
      if (x.second < y.second) {
        b = x.second;
        ib = x.pos_second;
      } else {
        b = y.second;
        ib = y.pos_second;
      }
    }
    return Node(a, ia, b, ib);
  }
  if (x.first < y.first) {
    a = x.first;
    ia = x.pos_first;
    if (x.pos_second == y.pos_first) {
      b = x.second;
      ib = x.pos_second;
    } else {
      if (x.second > y.first) {
        b = y.first;
        ib = y.pos_second;
      } else {
        b = x.second;
        ib = x.pos_second;
      }
    }
    return Node(a, ia, b, ib);
  }
  return Min(y, x);
}

int Log(int n) {
  int s = 0, p = 1;
  while (p * 2 <= n) {
    p *= 2;
    ++s;
  }
  return s;
}

struct SparceTable {
  int n;
  vector<vector<Node>> sparce;

  SparceTable(const vector<int>& q) {
    n = q.size();
    sparce.resize(Log(n) + 1, vector<Node>(n, Node(kInf, n + 1, kInf, n + 1)));
    for (int i = 0; i < Log(n) + 1; ++i) {
      for (int j = 0; j < n - (1 << i) + 1; ++j) {
        if (i == 0) {
          sparce[i][j] = Node(q[j], j, kInf, n + 1);
        } else {
          sparce[i][j] =
              Min(sparce[i - 1][j], sparce[i - 1][j + (1 << (i - 1))]);
        }
      }
    }
  }
  int Get(int left, int right) {
    int verh = Log(right - left);
    return Min(sparce[verh][left], sparce[verh][right - (1 << verh)]).second;
  }

};

signed main() {
  int n, q;
  cin >> n >> q;
  vector<int> mas(n);
  for (int i = 0; i < n; ++i) {
    cin >> mas[i];
  }
  SparceTable sparce(mas);
  int left, right;
  for (int i = 0; i < q; ++i) {
    cin >> left >> right;
    cout << sparce.Get(left - 1, right) << '\n';
  }
  return 0;
}