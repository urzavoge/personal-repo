#include <iostream>

#include <vector>


struct Pair {
  int64_t val;
  int index;
  Pair(int a, int b) : val(a), index(b) {}
};

void Siftup(std::vector<Pair>& heap, int v, std::vector<int>& request) {
  while ((v != 0) && (heap[v].val < heap[v / 2].val)) {
    std::swap(request[heap[v].index], request[heap[v / 2].index]);
    std::swap(heap[v], heap[v / 2]);
    v = v / 2;
  }
}

void Siftdown(std::vector<Pair>& heap, int v, std::vector<int>& request) {
  int n = heap.size();
  while (2 * v < n) {
    int u = 2 * v;
    if ((u + 1 < n) && (heap[u].val > heap[u + 1].val)) {
      u++;
    }
    if (heap[v].val <= heap[u].val) {
      break;
    }
    std::swap(request[heap[u].index], request[heap[v].index]);
    std::swap(heap[u], heap[v]);
    v = u;
  }
}

void Insert(std::vector<Pair>& heap, int64_t x, std::vector<int>& request,
            int xindex) {
  heap.push_back(Pair(x, xindex));
  int v = heap.size() - 1;
  request[xindex] = v;
  Siftup(heap, v, request);
}

void Getmin(std::vector<Pair>& heap) { std::cout << heap[0].val << '\n'; }

void Extractmin(std::vector<Pair>& heap, std::vector<int>& request) {
  int n = heap.size();
  std::swap(request[heap[n - 1].index], request[heap[0].index]);
  std::swap(heap[0], heap[n - 1]);
  heap.pop_back();
  Siftdown(heap, 0, request);
}

void DecreaseKey(std::vector<Pair>& heap, int index, int64_t delta,
                 std::vector<int>& request) {
  int v = request[index];
  heap[v].val -= delta;
  Siftup(heap, v, request);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int q;
  int64_t number1, number2;
  std::string what;
  std::cin >> q;
  std::vector<Pair> heap;
  std::vector<int> request(q + 1, 0);
  for (int i = 1; i <= q; ++i) {
    std::cin >> what;
    if (what == "insert") {
      std::cin >> number1;
      Insert(heap, number1, request, i);
    } else if (what == "getMin") {
      Getmin(heap);
    } else if (what == "extractMin") {
      Extractmin(heap, request);
    } else {
      std::cin >> number1 >> number2;
      DecreaseKey(heap, number1, number2, request);
    }
  }
  return 0;
}
