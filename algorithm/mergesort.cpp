#include <iostream>
#include <vector>
const int kMax = 100000;
struct node {
  int begin, end;
  node() = default;
  node(int right, int left) : begin(right), end(left) {}
  int Begin() { return begin; }
  int End() { return end; }
};
bool Comparator(node& a,node& b) {
  if (a.Begin() == b.Begin()) { return (a.End() < b.End()); }
  return (a.Begin() < b.Begin());
}
void Merge(std::vector<node>& a, int left, int mid, int right) {
  if (right - left == 1) { return; }
  std::vector<node> first(mid - left);
  std::vector<node> second(right - mid);
  for (int i = left; i < mid; ++i) {
    first[i - left] = a[i];
  }
  for (int i = mid; i < right; ++i) {
    second[i - mid] = a[i];
  }
  int i = left, j = 0, k = 0;
  while((j < mid - left) && (k < right - mid)) {
    if (Comparator(first[j], second[k])) {
      a[i] = first[j];
      j++; i++;
    } else {
      a[i] = second[k];
      k++; i++;
    }
  }
  while (j < mid - left)  {
    a[i] = first[j];
    j++; i++;
  }
  while (k < right - mid)  {
    a[i] = second[k];
    k++; i++;
  }
}

void Mergesort(std::vector<node>& a, int left,  int right) {
  if (right - left == 1) { return; }
  int mid = (left + right) / 2;
  Mergesort(a, left, mid);
  Mergesort(a, mid, right);
  Merge(a, left, mid, right);
}

 void Getvector(std::vector<node>& a, int n) {
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    a[i] = node(x, y);
  }
}

void Givevector(std::vector<node>& a, int n){
  for (int i = 0; i < n; ++i) {
    std::cout << a[i].Begin() << " " << a[i].End() << '\n';
  }
}


int main() {
  int n;
  std::cin >> n;
  std::vector<node> a(n), result;
  Getvector(a, n);
  Mergesort(a, 0, n);
  int begin = a[0].Begin(), end = a[0].End();
  int kol = 1;
  for (int i = 1; i < n; ++i) {
    if (a[i].Begin() > end) {
      result.push_back(node(begin, end));
      begin = a[i].Begin();
      end = a[i].End();
      ++kol;
    } else {
      if (a[i].End() > end) { end = a[i].End(); }
    }
  }
  result.push_back(node(begin,end));
  std::cout << kol <<'\n';
  Givevector(result,kol);

  return 0;
}

