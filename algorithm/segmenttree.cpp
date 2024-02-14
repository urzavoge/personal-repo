#include <iostream>

#include <vector>

using std::vector, std::cin, std::cout;

struct SegmentTree {
  vector<int64_t> tree;
  int64_t n;

  SegmentTree(const vector<int64_t>& q) {
    n = q.size();
    tree.resize(4 * n);
    Build(1, 0, n, q);
  }

  void Build(int64_t vertex, int64_t left, int64_t right,
             const vector<int64_t>& q) {
    if (left == right - 1) {
      if (left % 2 == 0) {
        tree[vertex] = q[left];
      } else {
        tree[vertex] = -q[left];
      }
      return;
    }
    int64_t mid = (left + right) / 2;
    Build(2 * vertex, left, mid, q);
    Build(2 * vertex + 1, mid, right, q);
    tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
  }

  int64_t Sum(int64_t ver, int64_t left, int64_t right, int64_t use_l,
              int64_t use_r) {
    if (use_l >= right || left >= use_r) {
      return 0;
    }
    if (left >= use_l && use_r >= right) {
      return tree[ver];
    }
    int64_t mid = (left + right) / 2;
    return Sum(2 * ver, left, mid, use_l, use_r) +
           Sum(2 * ver + 1, mid, right, use_l, use_r);
  }

  int64_t Sum(int64_t use_l, int64_t use_r) {
    return Sum(1, 0, n, use_l, use_r);
  }

  void Change(int64_t ver, int64_t left, int64_t right, int64_t ind,
              int64_t x) {
    if (left == right - 1) {
      tree[ver] = x;
      return;
    }
    int64_t mid = (left + right) / 2;
    if (ind < mid) {
      Change(2 * ver, left, mid, ind, x);
    } else {
      Change(2 * ver + 1, mid, right, ind, x);
    }
    tree[ver] = tree[2 * ver] + tree[2 * ver + 1];
  }
};

signed main() {
  int64_t n, m;
  cin >> n;
  vector<int64_t> q(n);
  for (int64_t i = 0; i < n; ++i) {
    cin >> q[i];
  }
  SegmentTree tree(q);
  cin >> m;
  int what;
  int64_t first, second;
  for (int64_t i = 0; i < m; ++i) {
    cin >> what >> first >> second;
    if (what == 0) {
      if (first % 2 == 0) {
        tree.Change(1, 0, n, first - 1, -second);
      } else {
        tree.Change(1, 0, n, first - 1, second);
      }
    } else {
      int ans = tree.Sum(first - 1, second);
      if (first % 2 == 1) {
        cout << ans << '\n';
      } else {
        cout << -ans << '\n';
      }
    }
  }
  return 0;
}