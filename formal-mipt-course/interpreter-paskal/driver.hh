#pragma once

#include "parser.hh"
#include "scanner.h"
#include <cassert>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class break_cycle : public std::exception {};

class abort_program : public std::exception {};

class Expression;
class Program;

enum Type { NO, INT, STR, BOOL };

class Driver {
public:
  Driver();
  std::unordered_map<std::string, int> var_int;
  std::unordered_map<std::string, Type> var_type;
  std::unordered_map<std::string, std::string> var_str;
  std::unordered_map<std::string, bool> var_bool;
  bool parse(const std::string &f);
  std::string file;

  std::shared_ptr<Program> program;

  void scan_begin();
  void scan_end();
  ~Driver() = default;

  bool trace_parsing;
  bool trace_scanning;
  yy::location location;

  friend class Scanner;
  Scanner scanner;
  yy::parser parser;
  bool location_debug;

private:
  std::ifstream stream;
};

class Expression {
public:
  int virtual eval() = 0;

  virtual ~Expression() = default;
};

class NumExp : public Expression {
public:
  int eval() final { return value_; }

  explicit NumExp(int value) : value_(value) {}

  ~NumExp() override = default;

private:
  int value_;
};

class AddExp : public Expression {
public:
  int eval() final { return left_->eval() + right_->eval(); }

  AddExp(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  ~AddExp() override = default;

private:
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;
};

class MulExp : public Expression {
public:
  int eval() final { return left_->eval() * right_->eval(); }

  MulExp(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  ~MulExp() override = default;

private:
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;
};

class MinusExp : public Expression {
public:
  int eval() final { return left_->eval() - right_->eval(); }

  MinusExp(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  ~MinusExp() override = default;

private:
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;
};

class DivExp : public Expression {
public:
  int eval() final { return left_->eval() / right_->eval(); }

  DivExp(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  ~DivExp() override = default;

private:
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;
};

class ModExp : public Expression {
public:
  int eval() final { return left_->eval() % right_->eval(); }

  ModExp(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  ~ModExp() override = default;

private:
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;
};

class NegExp : public Expression {
public:
  int eval() final { return -(left_->eval()); }

  explicit NegExp(std::shared_ptr<Expression> left) : left_(std::move(left)) {}

  ~NegExp() override = default;

private:
  std::shared_ptr<Expression> left_;
};

class IdentExp : public Expression {
public:
  int eval() final {
    if (driver_->var_type[ident_] != INT) {
      std::cout << "Expected type integer for variable " << ident_ << std::endl;
      throw abort_program();
    }
    return driver_->var_int[ident_];
  }

  IdentExp(Driver *driver, std::string ident)
      : driver_(driver), ident_(std::move(ident)) {}

  ~IdentExp() override = default;

private:
  Driver *driver_;
  std::string ident_;
};

class Condition {
public:
  bool virtual eval() = 0;
  virtual ~Condition() = default;
};

class BoolCond : public Condition {
  bool val_;

public:
  BoolCond(bool val) : val_(val) {}

  bool eval() final {
    return val_;
  }

  ~BoolCond() override = default;
};

class EqualCond : public Condition {
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;

public:
  EqualCond(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  bool eval() final { return left_->eval() == right_->eval(); }

  ~EqualCond() override = default;
};

class NotEqualCond : public Condition {
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;

public:
  NotEqualCond(std::shared_ptr<Expression> left,
               std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  bool eval() final { return left_->eval() != right_->eval(); }

  ~NotEqualCond() override = default;
};

class LessCond : public Condition {
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;

public:
  LessCond(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  bool eval() final { return left_->eval() < right_->eval(); }

  ~LessCond() override = default;
};

class LessOrEqCond : public Condition {
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;

public:
  LessOrEqCond(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  bool eval() final { return left_->eval() <= right_->eval(); }

  ~LessOrEqCond() override = default;
};

class GreaterOrEqCond : public Condition {
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;

public:
  GreaterOrEqCond(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  bool eval() final { return left_->eval() >= right_->eval(); }

  ~GreaterOrEqCond() override = default;
};

class GreaterCond : public Condition {
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;

public:
  GreaterCond(std::shared_ptr<Expression> left,
              std::shared_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  bool eval() final { return left_->eval() > right_->eval(); }

  ~GreaterCond() override = default;
};

class ExpCond : public Condition {
  std::shared_ptr<Expression> exp_;

public:
  explicit ExpCond(std::shared_ptr<Expression> exp) : exp_(std::move(exp)) {}

  bool eval() final { return static_cast<bool>(exp_->eval()); }

  ~ExpCond() override = default;
};

class IdentCond : public Condition {
  Driver *driver_;
  std::string ident_;

public:
  IdentCond(Driver *driver, std::string ident)
      : driver_(driver), ident_(std::move(ident)) {}

  bool eval() final {
    if (driver_->var_type[ident_] != BOOL) {
      std::cout << "Expected type bool for variable " << ident_ << std::endl;
      throw abort_program();
    }
    return driver_->var_bool[ident_];
  }

  ~IdentCond() override = default;
};

class AndCond : public Condition {
  std::shared_ptr<Condition> left_;
  std::shared_ptr<Condition> right_;

public:
  AndCond(std::shared_ptr<Condition> left, std::shared_ptr<Condition> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  bool eval() final { return left_->eval() && right_->eval(); }

  ~AndCond() override = default;
};

class OrCond : public Condition {
  std::shared_ptr<Condition> left_;
  std::shared_ptr<Condition> right_;

public:
  OrCond(std::shared_ptr<Condition> left, std::shared_ptr<Condition> right)
      : left_(std::move(left)), right_(std::move(right)) {}

  bool eval() final { return left_->eval() || right_->eval(); }

  ~OrCond() override {
    left_->~Condition();
    right_->~Condition();
  }
};

class NotCond : public Condition {
  std::shared_ptr<Condition> left_;

public:
  explicit NotCond(std::shared_ptr<Condition> left) : left_(std::move(left)) {}

  bool eval() final { return !left_->eval(); }

  ~NotCond() override = default;
};

class Line {
public:
  void virtual execute() = 0;
  virtual ~Line() = default;
};

class BreakLine : public Line {
public:
  BreakLine() = default;

  void execute() final {
    throw break_cycle();
  }

  ~BreakLine() override = default;
};

class AssStrLine : public Line {
  Driver *driver_;
  std::string ident_;
  std::string str_;

public:
  AssStrLine(Driver *driver, std::string ident, std::string str)
      : driver_(driver), ident_(std::move(ident)), str_(std::move(str)) {}

  void execute() final {
    if (driver_->var_type[ident_] != STR) {
      std::cout << "Expected type str for variable " << ident_ << std::endl;
      throw abort_program();
    }
    driver_->var_str[ident_] = str_.substr(1, str_.size() - 2);
  }

  ~AssStrLine() override = default;
};

class AssIntLine : public Line {
public:
  void execute() final {
    if (driver_->var_type[ident_] != INT) {
      std::cout << "Expected type integer for variable " << ident_ << std::endl;
      throw abort_program();
    }
    driver_->var_int[ident_] = exp_->eval();
  }
  AssIntLine(Driver *driver, std::string ident, std::shared_ptr<Expression> exp)
      : driver_(driver), ident_(std::move(ident)), exp_(std::move(exp)) {}

  ~AssIntLine() override = default;

private:
  Driver *driver_;
  std::string ident_;
  std::shared_ptr<Expression> exp_;
};

class AssBoolLine : public Line {
public:
  void execute() final {
    if (driver_->var_type[ident_] != BOOL) {
      std::cout << "Expected type bool for variable " << ident_ << std::endl;
      throw abort_program();
    }
    driver_->var_bool[ident_] = cond_->eval();
  }
  AssBoolLine(Driver *driver, std::string ident,
              std::shared_ptr<Condition> cond)
      : driver_(driver), ident_(std::move(ident)), cond_(std::move(cond)) {}

  ~AssBoolLine() override = default;

private:
  Driver *driver_;
  std::string ident_;
  std::shared_ptr<Condition> cond_;
};

class PrintLine : public Line {
  std::shared_ptr<Expression> exp_;

public:
  explicit PrintLine(std::shared_ptr<Expression> exp) : exp_(std::move(exp)) {}
  void execute() final { std::cout << exp_->eval() << std::endl; }

  ~PrintLine() override = default;
};

class PrintStrLine : public Line {
  std::string str_;

public:
  explicit PrintStrLine(std::string str) : str_(std::move(str)) {}
  void execute() final {
    std::cout << str_.substr(1, str_.size() - 2) << std::endl;
  }

  ~PrintStrLine() override = default;
};

class PrintIdentLine : public Line {
  Driver *driver_;
  std::string ident_;

public:
  PrintIdentLine(Driver *driver, std::string ident)
      : driver_(driver), ident_(std::move(ident)) {}

  void execute() final {
    if (driver_->var_type[ident_] == INT) {
      std::cout << driver_->var_int[ident_] << std::endl;
    } else if (driver_->var_type[ident_] == STR) {
      std::cout << driver_->var_str[ident_] << std::endl;
    } else if (driver_->var_type[ident_] == BOOL) {
      std::cout << driver_->var_bool[ident_] << std::endl;
    } else {
      std::cout << "Unknown variable " << ident_ << std::endl;
      throw abort_program();
    }
  }
  ~PrintIdentLine() override = default;
};

class Lines {
  std::vector<std::shared_ptr<Line>> lines_;

public:
  Lines() = default;
  Lines(std::shared_ptr<Line> line) : lines_(1, std::move(line)) {}

  static std::shared_ptr<Lines> Add(std::shared_ptr<Lines> other,
                                    std::shared_ptr<Line> line) {
    other->lines_.emplace_back(std::move(line));
    return other;
  }

  void execute_lines() {
    for (auto &line : lines_) {
      line->execute();
    }
  }

  ~Lines() = default;
};

class EmptyLine : public Line {
public:
  void execute() final {}
  EmptyLine() = default;
  ~EmptyLine() override = default;
};

class ForLine : public Line {
  Driver *driver_;
  std::shared_ptr<Expression> start_;
  std::shared_ptr<Expression> end_;
  std::string indent_;
  std::shared_ptr<Lines> lines_;

public:
  ForLine(Driver *driver, std::shared_ptr<Expression> start,
          std::shared_ptr<Expression> end, std::string indent,
          std::shared_ptr<Lines> lines)
      : driver_(driver), start_(std::move(start)), end_(std::move(end)),
        indent_(std::move(indent)), lines_(std::move(lines)) {}

  void execute() final {
    driver_->var_int[indent_] = start_->eval();
    for (int i = start_->eval(); i <= end_->eval();
         ++i, ++(driver_->var_int[indent_])) {
      try {
        lines_->execute_lines();
      } catch (break_cycle& except) {
        break;
      }
      if (i == end_->eval()) {
        break;
      }
    }
  }

  ~ForLine() override = default;
};

class WhileLine : public Line {
  std::shared_ptr<Condition> cond_;
  std::shared_ptr<Lines> lines_;

public:
  WhileLine(std::shared_ptr<Condition> cond, std::shared_ptr<Lines> lines)
      : cond_(std::move(cond)), lines_(std::move(lines)) {}

  void execute() final {
    while (cond_->eval()) {
      try {
        lines_->execute_lines();
      } catch (break_cycle& except) {
        break;
      }
    }
  }

  ~WhileLine() override = default;
};

class CaseLine : public Line {
  std::shared_ptr<Condition> condition_;
  std::shared_ptr<Lines> lines_;
  std::shared_ptr<Lines> else_lines_;
  bool if_only_;

public:
  CaseLine(std::shared_ptr<Condition> condition, std::shared_ptr<Lines> lines)
      : condition_(std::move(condition)), lines_(std::move(lines)),
        else_lines_(nullptr), if_only_(true) {}

  CaseLine(std::shared_ptr<Condition> condition, std::shared_ptr<Lines> lines,
           std::shared_ptr<Lines> else_lines)
      : condition_(std::move(condition)), lines_(std::move(lines)),
        else_lines_(std::move(else_lines)), if_only_(false) {}

  void execute() final {
    if (condition_->eval()) {
      lines_->execute_lines();
    } else {
      if (!if_only_) {
        else_lines_->execute_lines();
      }
    }
  }

  ~CaseLine() override = default;
};

class Declaration {
public:
  void virtual declare() = 0;
  virtual ~Declaration() = default;
};

class EmptyDecl : public Declaration {
public:
  void declare() final {}
  EmptyDecl() = default;
  ~EmptyDecl() override = default;
};

class IntDecl : public Declaration {
  Driver *driver_;
  std::shared_ptr<std::vector<std::string>> idents_;

public:
  IntDecl(Driver *driver, std::shared_ptr<std::vector<std::string>> idents)
      : driver_(driver), idents_(std::move(idents)) {}

  void declare() final {
    for (auto &ident : *idents_) {
      driver_->var_type[ident] = INT;
      driver_->var_int[ident] = 0;
    }
  }
};

class StrDecl : public Declaration {
  Driver *driver_;
  std::shared_ptr<std::vector<std::string>> idents_;

public:
  StrDecl(Driver *driver, std::shared_ptr<std::vector<std::string>> idents)
      : driver_(driver), idents_(std::move(idents)) {}

  void declare() final {
    for (auto &ident : *idents_) {
      driver_->var_type[ident] = STR;
      driver_->var_str[ident] = "";
    }
  }
};

class BoolDecl : public Declaration {
  Driver *driver_;
  std::shared_ptr<std::vector<std::string>> idents_;

public:
  BoolDecl(Driver *driver, std::shared_ptr<std::vector<std::string>> idents)
      : driver_(driver), idents_(std::move(idents)) {}

  void declare() final {
    for (auto &ident : *idents_) {
      driver_->var_type[ident] = BOOL;
      driver_->var_bool[ident] = false;
    }
  }
};

class Declarations {
  std::vector<std::shared_ptr<Declaration>> declarations_;

public:
  Declarations() = default;

  static std::shared_ptr<Declarations> Add(std::shared_ptr<Declarations> other,
                                           std::shared_ptr<Declaration> decl) {
    other->declarations_.emplace_back(std::move(decl));
    return other;
  }

  void execute_decls() {
    for (auto &decl : declarations_) {
      decl->declare();
    }
  }

  ~Declarations() = default;
};

class Program {
  std::shared_ptr<Declarations> declarations_;
  std::shared_ptr<Lines> lines_;

public:
  void set_decls(std::shared_ptr<Declarations> decls) {
    declarations_ = std::move(decls);
  }

  void set_lines(std::shared_ptr<Lines> lines) { lines_ = std::move(lines); }

  void execute_program() {
    declarations_->execute_decls();
    try {
      lines_->execute_lines();
    } catch (...) {
      std::cout << "Aborted" << std::endl;
    }
  }

  static std::shared_ptr<std::vector<std::string>>
  Add(std::shared_ptr<std::vector<std::string>> &idents, std::string &ident) {
    idents->emplace_back(ident);
    return idents;
  }

  ~Program() = default;
};
