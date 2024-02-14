#include <iostream>

#include <string>

#include <algorithm>

const int kMaxn = 1000 * 1000 * 2;

struct Stack {
    int* a = new int[kMaxn];
    int end = 0;
    int Size() { return end; }
    void Push(int x) {
      a[end] = x;
      end++;
    }
    int Pop() {
      end--;
      return a[end];
    }
    int Back() { return a[end - 1]; }
    ~Stack() { delete[] a; }
};

void Restore(Stack& add, Stack& add_min, Stack& remove, Stack& remove_min) {
  if (remove.Size() == 0) {
    while (add.Size() != 0) {
      int x = add.Back();
      add.Pop();
      add_min.Pop();
      remove.Push(x);
      if (remove_min.Size() != 0) {
        remove_min.Push(std::min(x, remove_min.Back()));
      } else {
        remove_min.Push(x);
      }
    }
  }
}

void Dequeue(Stack& remove, Stack& remove_min) {
  if (remove.Size() == 0) {
    std::cout << "error\n";
  } else {
    std::cout << remove.Pop() << '\n';
    remove_min.Pop();
  }
}

void Enqueue(Stack& add, Stack& add_min, int n) {
  add.Push(n);
  if (add_min.Size() != 0) {
    add_min.Push(std::min(n, add_min.Back()));
  } else {
    add_min.Push(n);
  }
  std::cout << "ok\n";
}

void Front(Stack& remove) {
  if (remove.Size() == 0) {
    std::cout << "error\n";
  } else {
    std::cout << remove.Back() << '\n';
  }
}

void Size(Stack& add, Stack& remove) {
  std::cout << add.Size() + remove.Size() << '\n';
}

void Clear(Stack& add, Stack& add_min, Stack& remove, Stack& remove_min) {
  while (add.Size() != 0) {
    add.Pop();
    add_min.Pop();
  }
  while (remove.Size() != 0) {
    remove.Pop();

    remove_min.Pop();
  }
  std::cout << "ok\n";
}

void Min(Stack& add_min, Stack& remove_min) {
  if (add_min.Size() == 0 && remove_min.Size() == 0) {
    std::cout << "error\n";
  } else if (add_min.Size() == 0) {
    std::cout << remove_min.Back() << '\n';
  } else if (remove_min.Size() == 0) {
    std::cout << add_min.Back() << '\n';
  } else {
    std::cout << std::min(add_min.Back(), remove_min.Back()) << '\n';
  }
}

int main() {
  Stack add, add_min, remove, remove_min;
  int m, n;
  std::string qw;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::cin >> qw;
    if (qw == "enqueue") {
      std::cin >> n;
      Enqueue(add, add_min, n);
    } else if (qw == "dequeue") {
      Restore(add, add_min, remove, remove_min);
      Dequeue(remove, remove_min);
    } else if (qw == "front") {
      Restore(add, add_min, remove, remove_min);
      Front(remove);
    } else if (qw == "size") {
      Size(add, remove);
    } else if (qw == "clear") {
      Clear(add, add_min, remove, remove_min);
    } else {
      Min(add_min, remove_min);
    }
  }
  return 0;
}
