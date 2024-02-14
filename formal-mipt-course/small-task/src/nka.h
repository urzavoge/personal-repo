#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Transition;

// структура для состояний
struct Condition {
  std::list<Transition> trans;
  bool is_end = false;

  Condition() = default;
  Condition(const std::list<Transition>& other, bool is_end)
      : trans(other), is_end(is_end) {}
};

//структура для переходов
struct Transition {
  std::string word;
  size_t num_to = 0;

  Transition() = default;
  Transition(std::string&& other, size_t num_to)
      : word(std::move(other)), num_to(num_to) {}
};


//конечный недетерминированный автомат
class NFA {
protected:
  std::vector<Condition> graph;
  std::unordered_set<char> alphabet;

public:
  NFA() = default;
  NFA(const std::vector<Condition>& other, const std::unordered_set<char>& alpha)
      : graph(other), alphabet(alpha) {}

  NFA(const NFA& other) = default;
  NFA(NFA&& other) = default;

  NFA& operator=(const NFA& other) = default;
  NFA& operator=(NFA&& other) = default;

  ~NFA() = default;

  // конструктор от char-a для создания из регулярки
  explicit NFA(char a) {
    if (a != '1') {
      alphabet.insert(a);
    }
    graph.emplace_back(std::list<Transition>{}, false);
    graph.emplace_back(std::list<Transition>{}, true);
    graph[0].trans.emplace_back(std::string(1, a), 1);
    if (graph[0].trans.begin()->word == "1") {
      graph[0].trans.begin()->word = "";
    }
  }

  // оператор + для создания из регулярки
  // подсоединяем два автомата "параллельно"
  NFA& operator+=(const NFA& second) {
    std::vector<Condition> sum_graph;
    sum_graph.emplace_back();
    sum_graph[0].trans.emplace_back("", 1);
    for (auto& cond: this->graph) {
      for (auto& edge: cond.trans) {
        edge.num_to += 1;
      }
      sum_graph.emplace_back(cond);
    }
    sum_graph.back().is_end = false;
    size_t fake_end = sum_graph.size();
    sum_graph[0].trans.emplace_back("", fake_end);
    for (auto& cond: second.graph) {
      sum_graph.emplace_back(cond);
      for (auto& edge: sum_graph.back().trans) {
        edge.num_to += fake_end;
        alphabet.insert(edge.word[0]);
      }
    }
    sum_graph.back().is_end = false;
    sum_graph.emplace_back(std::list<Transition>(), true);
    sum_graph[fake_end - 1].trans.emplace_back("", sum_graph.size() - 1);
    sum_graph[sum_graph.size() - 2].trans.emplace_back("", sum_graph.size() - 1);
    graph = sum_graph;
    return *this;
  }

  // оператор *= для создания из регулярки
  // подсоединяем два автомата "последовательно"
  NFA& operator*=(const NFA& second) {
    size_t fake_end = graph.size();
    graph.back().is_end = false;
    graph.back().trans.emplace_back("", fake_end);
    for (auto& cond: second.graph) {
      graph.emplace_back(cond);
      for (auto& edge: graph.back().trans) {
        alphabet.insert(edge.word[0]);
        edge.num_to += fake_end;
      }
    }
    return *this;
  }

  // оператор * для создания из регулярки
  // делает итерацию клини для автомата
  void operator*() {
    graph.back().trans.emplace_back("", 0);
    graph[0].trans.emplace_back("", graph.size() - 1);
  }

  size_t size() {
    return graph.size();
  }

  // разворачивает автомат
  // нужно, чтобы мы искали не суффикс, а префикс
  void reverse() {
    std::vector<Condition> inverted_graph(1 + graph.size());
    inverted_graph[1].is_end = true;
    for (size_t num = 0; num < graph.size(); ++num) {
      if (graph[num].is_end) {
        inverted_graph[0].trans.emplace_back("", num + 1);
      }
      for (auto& edge : graph[num].trans) {
        inverted_graph[edge.num_to + 1].trans.emplace_back(std::move(edge.word), num + 1);
      }
    }
    graph = inverted_graph;
  }

  // проверяет есть ли такой префикс
  bool dfs_for_prefix(std::vector<int>& prev_k, char x, int k, size_t num = 0) {
    if (k == 0) {
      return true;
    }
    prev_k[num] = k;
    for (const auto& edge : graph[num].trans) {
      if (edge.word[0] == x && dfs_for_prefix(prev_k, x, k - 1, edge.num_to)) {
        return true;
      }
      if (edge.word.empty()) {
        if (prev_k[edge.num_to] == -1 && dfs_for_prefix(prev_k, x, k, edge.num_to)) {
          return true;
        }
        if (prev_k[edge.num_to] != k && prev_k[edge.num_to] != -1) {
          return true;
        }
      }
    }
    prev_k[num] = -1;
    return false;
  }
};


// построение из регулярного выражения в обратной польской записи
NFA make_from_poland(const std::string& reg_in_poland) {
  std::stack<NFA> stack{};
  for (const auto let : reg_in_poland) {
    if (let == '+' && stack.size() >= 2) {
      NFA first = stack.top();
      stack.pop();
      NFA& second = stack.top();
      second += first;
    } else if (let == '.' && stack.size() >= 2) {
      NFA first = stack.top();
      stack.pop();
      NFA& second = stack.top();
      second *= first;
    } else if (let == '*' && !stack.empty()) {
      NFA& first = stack.top();
      *first;
    } else if (let != '+' && let != '*' && let != '.'){
      stack.emplace(let);
    } else {
      throw std::invalid_argument("bad regular expression representation");
    }
  }
  if (stack.size() == 1) {
    return stack.top();
  } else {
    throw std::invalid_argument("bad regular expression representation");
  }
}

// функция, решающая задачу
bool TaskSolver(const std::string& regular_expression, char x, int k) {
  NFA nfa = make_from_poland(regular_expression);
  nfa.reverse();
  std::vector<int> prev_k(nfa.size(), -1);
  return nfa.dfs_for_prefix(prev_k, x, k);
}