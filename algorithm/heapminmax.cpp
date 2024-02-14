#include <iostream>

#include <vector>

using std::cout;

using std::cin;

struct Pair {
  int64_t val;
  int index;
  Pair(int a, int b) : val(a), index(b) {}
};

void SiftupMin(std::vector<Pair>& heap_min, std::vector<Pair>& heap_max,
               int v) {
  while ((v != 0) && (heap_min[v].val < heap_min[(v - 1) / 2].val)) {
    std::swap(heap_max[heap_min[v].index].index,
              heap_max[heap_min[(v - 1) / 2].index].index);
    std::swap(heap_min[v], heap_min[(v - 1) / 2]);
    v = (v - 1) / 2;
  }
}

void SiftdownMin(std::vector<Pair>& heap_min, std::vector<Pair>& heap_max,
                 int v) {
  int n = heap_min.size();
  while (2 * v + 1 < n) {
    int u = 2 * v + 1;
    if ((u + 1 < n) && (heap_min[u].val > heap_min[u + 1].val)) {
      u++;
    }
    if (heap_min[v].val <= heap_min[u].val) {
      break;
    }
    std::swap(heap_max[heap_min[v].index].index,
              heap_max[heap_min[u].index].index);
    std::swap(heap_min[v], heap_min[u]);
    v = u;
  }
}

void SiftupMax(std::vector<Pair>& heap_max, std::vector<Pair>& heap_min,
               int v) {
  while ((v != 0) && (heap_max[v].val > heap_max[(v - 1) / 2].val)) {
    std::swap(heap_min[heap_max[v].index].index,
              heap_min[heap_max[(v - 1) / 2].index].index);
    std::swap(heap_max[v], heap_max[(v - 1) / 2]);
    v = (v - 1) / 2;
  }
}

void SiftdownMax(std::vector<Pair>& heap_max, std::vector<Pair>& heap_min,
                 int v) {
  int n = heap_max.size();
  while (2 * v + 1 < n) {
    int u = 2 * v + 1;
    if ((u + 1 < n) && (heap_max[u].val < heap_max[u + 1].val)) {
      u++;
    }
    if (heap_max[v].val >= heap_max[u].val) {
      break;
    }
    std::swap(heap_min[heap_max[v].index].index,
              heap_min[heap_max[u].index].index);
    std::swap(heap_max[v], heap_max[u]);
    v = u;
  }
}
void Insert(std::vector<Pair>& heap_min, std::vector<Pair>& heap_max,
            int64_t x) {
  int v1 = heap_max.size();
  int v2 = heap_min.size();
  heap_min.push_back(Pair(x, v1));
  heap_max.push_back(Pair(x, v2));
  SiftupMin(heap_min, heap_max, v2);
  SiftupMax(heap_max, heap_min, v1);
  cout << "ok" << '\n';
}

void Get(std::vector<Pair>& heap_min) {
  if (heap_min.empty()) {
    cout << "error" << '\n';
    return;
  }
  cout << heap_min[0].val << '\n';
}


void Extractmin(std::vector<Pair>& heap_min, std::vector<Pair>& heap_max) {
  int n = heap_min.size();
  if (n == 0) {
    cout << "error" << '\n';
    return;
  }
  Get(heap_min);
  int vmax = heap_min[0].index;
  std::swap(heap_max[heap_min[0].index].index,
            heap_max[heap_min[n - 1].index].index);
  std::swap(heap_min[0], heap_min[n - 1]);
  std::swap(heap_min[heap_max[vmax].index].index,
            heap_min[heap_max[n - 1].index].index);
  std::swap(heap_max[vmax], heap_max[n - 1]);
  heap_min.pop_back();
  SiftdownMin(heap_min, heap_max, 0);
  heap_max.pop_back();
  SiftdownMax(heap_max, heap_min, vmax);
  SiftupMax(heap_max, heap_min, vmax);
}

void Extractmax(std::vector<Pair>& heap_max, std::vector<Pair>& heap_min) {
  int n = heap_max.size();
  if (n == 0) {
    cout << "error" << '\n';
    return;
  }
  int vmin = heap_max[0].index;
  Get(heap_max);
  std::swap(heap_min[heap_max[0].index].index,
            heap_min[heap_max[n - 1].index].index);
  std::swap(heap_max[0], heap_max[n - 1]);
  std::swap(heap_max[heap_min[vmin].index].index,
            heap_max[heap_min[n - 1].index].index);
  std::swap(heap_min[vmin], heap_min[n - 1]);
  heap_max.pop_back();
  SiftdownMax(heap_max, heap_min, 0);
  heap_min.pop_back();
  SiftdownMin(heap_min, heap_max, vmin);
  SiftupMin(heap_min, heap_max, vmin);
}

void Size(std::vector<Pair>& heap_min) { cout << heap_min.size() << '\n'; }

void Clear(std::vector<Pair>& heap_max, std::vector<Pair>& heap_min) {
  while (!heap_min.empty()) {
    heap_min.pop_back();
  }
  while (!heap_max.empty()) {
    heap_max.pop_back();
  }
  cout << "ok" << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int q;
  int64_t number1;
  std::string what;
  cin >> q;
  std::vector<Pair> heap_min, heap_max;
  for (int i = 0; i < q; ++i) {
    cin >> what;
    if (what == "insert") {
      cin >> number1;
      Insert(heap_min, heap_max, number1);
    } else if (what == "get_min") {
      Get(heap_min);
    } else if (what == "extract_min") {
      Extractmin(heap_min, heap_max);
    } else if (what == "get_max") {
      Get(heap_max);
    } else if (what == "extract_max") {
      Extractmax(heap_max, heap_min);
    } else if (what == "size") {
      Size(heap_min);
    } else {
      Clear(heap_min, heap_max);
    }
  }
  return 0;
}
