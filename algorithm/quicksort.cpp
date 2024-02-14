#include <iostream>
#include <vector>

int Sort(std::vector<int>& a, int left, int right) {
  int i = left, j = right, p = a[(left + right)/2];
  while (i <= j) {
    while (a[i] < p) {
      ++i;
    }
    while (a[j] > p) {
      --j;
    }
    if (i >= j) {
      break;
    }
    std::swap(a[i++], a[j--]);
  }
  return j;
}
void Quicksort(std::vector<int>& a, int left, int right) {
  if (right - left <= 0) {
    return;
  }
  int pivo = Sort(a, left, right);
  Quicksort(a, left, pivo);
  Quicksort(a, pivo + 1, right);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  Quicksort(a, 0, n - 1);
  for (int i = 0; i < n; i++) {
    std::cout << a[i] << " ";
  }
  return 0;
}