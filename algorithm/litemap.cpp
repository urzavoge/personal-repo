#include <iostream>

#include <vector>

using std::vector, std::cin, std::cout, std::hash, std::string;

template <typename K, typename V>
struct Node {
  K key;
  V value;
  Node* son = nullptr;
  Node() = default;
  Node(K key, V value, Node* head) : key(key), value(value) { son = head; }
};

template <typename K, typename V>
struct HashTable {
  vector<Node<K, V>*> table;
  hash<K> generator;
  size_t cap;
  V piska = V();
  HashTable(size_t n) : cap(n) { table.resize(n, nullptr); }
  size_t Hash(K key) { return generator(key) % cap; }

  void Push(K key, V val) {
    if (Find(key)) {
      return;
    }
    table[Hash(key)] = new Node<K, V>(key, val, table[Hash(key)]);
  }

  bool Find(K key, Node<K, V>* head) {
    for (auto now = head; now != nullptr; now = now->son) {
      if (now->key == key) {
        return true;
      }
    }
    return false;
  }

  bool Find(K key) { return Find(key, table[Hash(key)]); }

  void Eraze(K key, Node<K, V>* head) {
    if (table[Hash(key)] == nullptr) {
      return;
    }
    if (table[Hash(key)]->key == key) {
      Node<K, V>* prev = table[Hash(key)];
      table[Hash(key)] = head->son;
      delete prev;
      return;
    }
    auto parent = head;
    auto now = head->son;
    for (; now != nullptr; parent = now, now = now->son) {
      if (now->key == key) {
        parent->son = now->son;
        delete now;
        return;
      }
    }
  }

  V& Get(K key, Node<K, V>* head) {
    if (!Find(key, head)) {
      Push(key, V());
      head = table[Hash(key)];
      return head->value;
    }
    for (Node<K, V>* now = head; now != nullptr; now = now->son) {
      if (now->key == key) {
        return now->value;
      }
    }
    return piska;
  }

  V& Get(K key) { return Get(key, table[Hash(key)]); }

  void Eraze(K key) { Eraze(key, table[Hash(key)]); }

  void Clear(Node<K, V>* head) {
    if (head == nullptr) {
      return;
    }
    Clear(head->son);
    delete head;
  }

  void Clear() {
    for (size_t i = 0; i < table.size(); ++i) {
      Clear(table[i]);
      table[i] = nullptr;
    }
  }

  ~HashTable() { Clear(); }
};

struct Star {
  size_t x, y;
  Star() = default;
  Star(size_t x, size_t y) : x(x), y(y) {}
  size_t Len(Star other) {
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
  }
};
int main() {
  size_t n, t, ans = 0;
  cin >> n >> t;
  if (t == 2) {
    cout << 0;
    return 0;
  }
  vector<Star> pole(n);
  size_t x, y;
  for (size_t i = 0; i < n; ++i) {
    cin >> x >> y;
    pole[i] = Star(x, y);
  }
  HashTable<size_t, size_t> table((n * (n + 1)) / 2);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      ++table.Get(pole[i].Len(pole[j]));
    }
    for (size_t j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      size_t prom = table.Get(pole[i].Len(pole[j]));
      ans += (prom * (prom - 1)) / 2;
      table.Eraze(pole[i].Len(pole[j]));
    }
  }
  cout << ans;
  return 0;
}