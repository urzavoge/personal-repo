#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
size_t Hash(const T& seq) {
  size_t mod = (1e9) + 7;
  size_t ans = 0;
  size_t base = 1;
  for (auto el : seq.nums) {
    ans = (ans + el * base) % mod;
    base *= seq.max_num;
  }
  return ans;
}

struct set_of_num {
  std::vector<size_t> nums;
  size_t hash;
  size_t max_num;

  set_of_num(const std::vector<size_t>& other, size_t max_num)
      : nums(other), hash(0), max_num(max_num) {
    std::sort(nums.begin(), nums.end());
    auto last = std::unique(nums.begin(), nums.end());
    nums.erase(last, nums.end());
    hash = Hash(*this);
  }

  bool operator==(const set_of_num& other) const { return hash == other.hash; }
};

namespace std {
template <>
struct hash<set_of_num> {
  auto operator()(const set_of_num& other) const -> size_t {
    return Hash<set_of_num>(other);
  }
};
}  // namespace std

struct Transition;

struct Condition {
  std::list<Transition> trans;
  bool is_end;

  Condition() = default;
  Condition(const std::list<Transition>& other, bool is_end)
      : trans(other), is_end(is_end) {}
};

struct Transition {
  std::string word;
  size_t num_to;

  Transition() = default;
  Transition(const std::string& other, size_t num_to)
      : word(other), num_to(num_to) {}
};

class NFA {
  std::vector<Condition> graph;
  std::unordered_set<char> alphabet;

  friend std::ostream& operator<<(std::ostream& out, const NFA& other);
  friend class DFA;
  friend NFA make(std::string regular_expression);

  bool dfs_for_letters(size_t num, std::vector<bool>& used) {
    used[num] = true;
    bool ans = true;
    for (auto edge : graph[num].trans) {
      if (edge.word.size() != 1) {
        return false;
      }
      if (!used[edge.num_to]) {
        ans &= dfs_for_letters(edge.num_to, used);
      }
    }
    return ans;
  }

  void dfs_for_erasing(size_t num, std::vector<bool>& used) {
    used[num] = true;
    for (auto edge : graph[num].trans) {
      if (!used[edge.num_to]) {
        dfs_for_erasing(edge.num_to, used);
      }
    }
  }

  void compress(size_t num, Transition& edge) {
    for (auto next_edge : graph[edge.num_to].trans) {
      graph[num].trans.emplace_back(next_edge.word, next_edge.num_to);
    }
    if (graph[edge.num_to].is_end || graph[num].is_end) {
      graph[num].is_end = graph[edge.num_to].is_end = true;
    }
  }

 public:
  NFA() = default;
  NFA(const std::vector<Condition>& other, std::unordered_set<char> alpha)
      : graph(other), alphabet(alpha) {}

  struct Edge {
    size_t from;
    size_t to;
    std::string word;
  };

  NFA(const std::vector<Edge>& edges, const std::vector<size_t> finishes) {
    size_t size = 0;
    for (auto& edge : edges) {
      size = std::max(size, std::max(edge.from, edge.to));
      for (auto letter : edge.word) {
        alphabet.insert(letter);
      }
    }
    graph.resize(size + 1, Condition(std::list<Transition>(), false));
    for (auto& edge : edges) {
      graph[edge.from].trans.emplace_back(edge.word, edge.to);
    }
    for (auto& num : finishes) {
      graph[num].is_end = true;
    }
  }

  bool one_letter() {
    std::vector<bool> used(graph.size(), false);
    bool ans = true;
    for (size_t i = 0; i < used.size(); ++i) {
      if (!used[i]) ans &= dfs_for_letters(i, used);
    }
    return ans;
  }

  void EraseExtra() {
    std::vector<bool> used(graph.size(), false);
    dfs_for_erasing(0, used);
    if (used == std::vector<bool>(graph.size(), true)) {
      return;
    }
    std::vector<Condition> new_conds;
    std::vector<size_t> now_is(graph.size(), 0);
    for (size_t num = 0; num < graph.size(); ++num) {
      if (used[num]) {
        now_is[num] = new_conds.size();
        new_conds.emplace_back(graph[num]);
      }
    }
    for (auto& conds : new_conds) {
      for (auto& edge : conds.trans) {
        edge.num_to = now_is[edge.num_to];
      }
    }
    graph = new_conds;
  }

  void MakeSimplier() {
    for (size_t num = 0; num < graph.size(); ++num) {
      for (auto iter = graph[num].trans.begin(); iter != graph[num].trans.end();
           ++iter) {
        auto& edge = *iter;
        if (edge.word.size() > 1) {
          std::string copy = edge.word;
          size_t to = edge.num_to;

          graph.emplace_back(std::list<Transition>(), false);
          edge.num_to = graph.size() - 1;
          edge.word = copy[0];

          copy.erase(copy.begin());
          graph.back().trans.emplace_back(copy, to);
        }
      }
    }
  }

  void DeleteEmpties() {
    std::queue<size_t> check;
    std::vector<bool> used(graph.size(), false);
    check.push(0);
    while (!check.empty()) {
      size_t num = check.front();
      used[num] = true;
      check.pop();
      for (auto edge_it = graph[num].trans.begin();
           edge_it != graph[num].trans.end();) {
        Transition& edge = *edge_it;
        if (!used[edge.num_to]) {
          check.push(edge.num_to);
        }
        ++edge_it;
        if (edge.word == "") {
          compress(num, edge);
          auto terrorist = edge_it;
          graph[num].trans.erase(--terrorist);
        }
      }
    }
    EraseExtra();
  }

  void MakeCute() {
    EraseExtra();
    MakeSimplier();
    DeleteEmpties();
  }

  NFA Tompson() {
    MakeCute();
    std::unordered_map<set_of_num, size_t> get_num{};
    std::vector<const set_of_num> get_set(
        1, set_of_num(std::vector<size_t>{0}, graph.size()));
    get_num[get_set[0]] = 0;

    NFA dfa{std::vector<Condition>(
                1, Condition{std::list<Transition>(), graph[0].is_end}),
            alphabet};
    std::queue<size_t> check;
    check.push(0);

    while (!check.empty()) {
      size_t num = check.front();
      check.pop();
      for (auto letter : alphabet) {
        std::vector<size_t> achievable;
        bool is_end = false;
        for (auto num_in_set : get_set[num].nums) {
          for (auto edge : graph[num_in_set].trans) {
            if (edge.word == std::string(1, letter)) {
              achievable.push_back(edge.num_to);
              if (graph[edge.num_to].is_end) {
                is_end = true;
              }
            }
          }
        }
        if (achievable.empty()) {
          continue;
        }
        const set_of_num new_vertex(achievable, graph.size());
        if (!get_num.contains(new_vertex)) {
          get_num[new_vertex] = dfa.graph.size();
          get_set.push_back(new_vertex);
          dfa.graph.emplace_back(std::list<Transition>(), is_end);
          check.push(get_num[new_vertex]);
        }
        dfa.graph[num].trans.emplace_back(std::string(1, letter),
                                          get_num[new_vertex]);
      }
    }
    return dfa;
  }
};

NFA Make(std::string regular_expression) {
  if (regular_expression.size() == 1) {
    NFA nfa(std::vector<Condition>{},
            std::unordered_set<char>{regular_expression[0]});
    nfa.graph.emplace_back(std::list<Transition>{}, false);
    nfa.graph.emplace_back(std::list<Transition>{}, true);
    nfa.graph[0].trans.emplace_back(regular_expression, 1);
    return nfa;
  }
  if (regular_expression.back() == '*') {
    regular_expression.erase(regular_expression.begin());
    regular_expression.erase(--regular_expression.end());
    regular_expression.erase(--regular_expression.end());
    NFA old = make(regular_expression);
    old.graph.back().trans.emplace_back("", 0);
    return old;
  }
  int count = 0;
  for (size_t i = 0; i < regular_expression.size(); ++i) {
    char let = regular_expression[i];
    if (let == '(' || let == ')') {
      count += (let == '(' ? 1 : -1);
    }
    if (count == 0) {
      if (regular_expression[i + 1] == '(') {
        NFA first = make(regular_expression.substr(1, i - 1));
        NFA second = make(regular_expression.substr(
            i + 2, regular_expression.size() - i - 3));
        size_t fake_end = first.graph.size();
        first.graph.back().is_end = false;
        first.graph.back().trans.emplace_back("", fake_end);
        for (auto& cond : second.graph) {
          for (auto& edge : cond.trans) {
            first.alphabet.insert(edge.word[0]);
            edge.num_to += fake_end;
          }
          first.graph.emplace_back(cond);
        }
        return first;
      }
      if (regular_expression[i + 1] == '+') {
        NFA first = make(regular_expression.substr(1, i - 1));
        NFA second = make(regular_expression.substr(
            i + 3, regular_expression.size() - i - 4));
        NFA nfa{};
        nfa.graph.emplace_back();
        nfa.graph[0].trans.emplace_back("", 1);
        for (auto& cond : first.graph) {
          for (auto& edge : cond.trans) {
            edge.num_to += 1;
            nfa.alphabet.insert(edge.word[0]);
          }
          nfa.graph.emplace_back(cond);
        }
        nfa.graph.back().is_end = false;
        size_t fake_end = nfa.graph.size();
        nfa.graph[0].trans.emplace_back("", fake_end);
        for (auto& cond : second.graph) {
          for (auto& edge : cond.trans) {
            edge.num_to += fake_end;
            nfa.alphabet.insert(edge.word[0]);
          }
          nfa.graph.emplace_back(cond);
        }
        nfa.graph.back().is_end = false;
        nfa.graph.emplace_back(std::list<Transition>(), true);
        nfa.graph[fake_end - 1].trans.emplace_back("", nfa.graph.size() - 1);
        nfa.graph[nfa.graph.size() - 2].trans.emplace_back("", nfa.graph.size() - 1);
        return nfa;
      }
    }
  }
  throw std::invalid_argument("bad regular expression representation");
}

class DFA {
  std::vector<Condition> graph;
  std::unordered_set<char> alphabet;

 public:
  DFA(NFA& other) : graph(other.Tompson().graph), alphabet(other.alphabet) {}

  void MakeFull() {
    bool flag = false;
    for (auto& cond : graph) {
      std::unordered_set<char> useless = alphabet;
      for (auto edge : cond.trans) {
        useless.erase(edge.word[0]);
      }
      for (auto letter : useless) {
        cond.trans.emplace_back(std::string(1, letter), graph.size());
        flag = true;
      }
    }
    if (flag) {
      graph.emplace_back(std::list<Transition>(), false);
      for (auto letter : alphabet) {
        graph.back().trans.emplace_back(std::string(1, letter),
                                        graph.size() - 1);
      }
    }
  }

  bool is_readable(std::string word) {
    MakeFull();
    size_t num = 0;
    while (word.size()) {
      for (auto edge : graph[num].trans) {
        if (edge.word[0] == word[0]) {
          num = edge.num_to;
          word.erase(word.begin());
          break;
        }
      }
    }
    return graph[num].is_end;
  }

  void print() {
    for (size_t num = 0; num < graph.size(); ++num) {
      for (auto edge : graph[num].trans) {
        std::cout << (graph[num].is_end ? "t" : "") << num << " "
                  << (graph[edge.num_to].is_end ? "t" : "") << edge.num_to
                  << " " << edge.word << '\n';
      }
    }
  }
};

std::ostream& operator<<(std::ostream& out, const NFA& other) {
  out << "alphabet:";
  for (auto letter : other.alphabet) {
    out << " " << letter;
  }
  out << std::endl;
  out << std::endl;
  for (size_t num = 0; num < other.graph.size(); ++num) {
    out << "vertex : " << num << ". is end - "
        << (other.graph[num].is_end ? "yes." : "no.") << std::endl;
    for (auto edge : other.graph[num].trans) {
      out << "    edge : to - " << edge.num_to << ". word - " << edge.word
          << "." << std::endl;
    }
    out << std::endl;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const DFA& other) {
  out << reinterpret_cast<const NFA&>(other);
  return out;
}