#include <iostream>
#include <vector>
#define int long long

using namespace std;

vector<int> Q(int n) {
  vector<int> res;
  for (int i = 2; i * i <= n; ++i) {
    int count = 0;
    while (n % i == 0) {
      n /= i;
      count++;
    }
    if (count != 0) {
      res.push_back(i);
    }
  }
  if (n != 1) {
    res.push_back(n);
  }
  return res;
}

int P(int n) {
  vector<int> f = Q(n);
  int res = n;
  for (int i = 0; i < f.size(); ++i) {
    res /= f[i];
  }
  for (int i = 0; i < f.size(); ++i) {
    res *= f[i] - 1;
  }
  return res;
}



signed main() {
  int64_t n;
  std::cin >> n;
  std::cout << P(n);
  return 0;
}
