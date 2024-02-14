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
int Quicksort(std::vector<int>& a, int left, int k, int right) {
  if (right - left <= 0) {
    return a[left];
  }
  int pivo = Sort(a, left, right);
  if (pivo == k) {
    return a[pivo];
  } else if (pivo > k) {
    return Quicksort(a, left, k, pivo);
  } else {
    return Quicksort(a, pivo + 1, k, right);
  }
}

int main() {
  int n,k;
  std::cin >> n >> k;
  std::vector<int> a(n);
  std::cin >> a[0] >> a[1];
  for (int i = 2; i < n; ++i) {
    a[i] = (123 * a[i - 1] + 45 * a[i - 2]) % (10 * 1000 * 1000 + 4321);
  }
  std::cout << Quicksort(a, 0, k - 1, n - 1);
  return 0;
}