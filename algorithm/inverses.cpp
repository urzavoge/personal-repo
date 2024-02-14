#include <iostream>
#include <vector>

int Merge(std::vector<int>& a, int left, int mid, int right) {
  if (right - left == 1) {
    return 0;
  }
  int kol = 0;
  std::vector<int> first(mid - left);
  std::vector<int> second(right - mid);
  for (int i = left; i < mid; ++i) {
    first[i - left] = a[i];
  }
  for (int i = mid; i < right; ++i) {
    second[i - mid] = a[i];
  }
  int i = left, j = 0, k = 0;
  while ((j < mid - left) && (k < right - mid)) {
    if (first[j] < second[k]) {
      a[i] = first[j];
      j++;
      i++;
    } else {
      a[i] = second[k];
      kol += mid - left - j;
      k++;
      i++;
    }
  }
  while (j < mid - left) {
    a[i] = first[j];
    j++;
    i++;
  }
  while (k < right - mid) {
    a[i] = second[k];
    k++;
    i++;
  }
  return kol;
}

int Mergesort(std::vector<int>& a, int left, int right) {
  if (right - left == 1) {
    return 0;
  }
  int kol = 0, mid = (left + right) / 2;
  kol += Mergesort(a, left, mid);
  kol += Mergesort(a, mid, right);
  kol += Merge(a, left, mid, right);
  return kol;
}

void Getvector(std::vector<int>& a, int n) {
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x;
    a[i] = x;
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  Getvector(a, n);
  std::cout << Mergesort(a, 0, n);

  return 0;
}