#include <cassert>

#include "src/nka.h"

void TestSuffix_1() {
  assert(!TaskSolver("ab+c.aba.*.bac.+.+*", 'a', 2));
  assert(TaskSolver("acb..bab.c.*.ab.ba.+.+*a.", 'c', 0));
  // (b*abb*)*
  assert(TaskSolver("b*a.b.b*.*", 'b', 23));
  assert(!TaskSolver("b*a.b.b*.*", 'a', 1));
}

void TestSuffix_2() {
  //   ((a+b)c*+d*c(ab)*)(dca*+b)
  assert(TaskSolver("ab+c*.d*c.ab.*.+dc.a*.b+.", 'a', 17));

  assert(!TaskSolver("ab+c*.d*c.ab.*.+dc.a*.b+.", 'd', 1));

  assert(TaskSolver("ab+c*.d*c.ab.*.+dc.a*.b+.", 'c', 1));
  assert(!TaskSolver("ab+c*.d*c.ab.*.+dc.a*.b+.", 'c', 2));

  assert(TaskSolver("ab+c*.d*c.ab.*.+dc.a*.b+.", 'b', 1));
  assert(TaskSolver("ab+c*.d*c.ab.*.+dc.a*.b+.", 'b', 2));
  assert(!TaskSolver("ab+c*.d*c.ab.*.+dc.a*.b+.", 'b', 3));
}

void TestSuffix_3() {
  //(a+b+c+d)*(abbb+bcccc+cdd+daaa)
  assert(TaskSolver("ab+c+d+*abbb...bcccc....+cdd..+daaa...+.", 'a', 3));
  assert(!TaskSolver("ab+c+d+*abbb...bcccc....+cdd..+daaa...+.", 'a', 4));

  assert(TaskSolver("ab+c+d+*abbb...bcccc....+cdd..+daaa...+.", 'b', 3));
  assert(!TaskSolver("ab+c+d+*abbb...bcccc....+cdd..+daaa...+.", 'b', 4));

  assert(TaskSolver("ab+c+d+*abbb...bcccc....+cdd..+daaa...+.", 'c', 4));
  assert(!TaskSolver("ab+c+d+*abbb...bcccc....+cdd..+daaa...+.", 'c', 5));

  assert(TaskSolver("ab+c+d+*abbb...bcccc....+cdd..+daaa...+.", 'd', 2));
  assert(!TaskSolver("ab+c+d+*abbb...bcccc....+cdd..+daaa...+.", 'd', 3));
}

void TestSuffix_4() {
  //(1 + a* + bc)*
  // тут точно есть переходы по eps в одну и ту же вершину,
  // так как они образуются при сложении автоматов.
  assert(TaskSolver("1a*+bc.+*", 'a', 17));
  assert(!TaskSolver("1a*+bc.+*", 'b', 1));
  assert(TaskSolver("1a*+bc.+*", 'c', 1));
  assert(!TaskSolver("1a*+bc.+*", 'c', 2));
  try {
    TaskSolver("1+++", 'a', 0);
    assert(false);
  } catch (...) {
    assert(true);
  }
}

int main() {

  TestSuffix_1();
  TestSuffix_2();
  TestSuffix_3();
  TestSuffix_4();
  std::cout << "Test suffix passed" << std::endl;

  return 0;
}