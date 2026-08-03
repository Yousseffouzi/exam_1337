#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"

#include <iostream>
#include <sstream>
#include <string>

/* ------------------------------------------------------------------ */
/*  Tiny test harness                                                 */
/* ------------------------------------------------------------------ */

static int g_pass = 0;
static int g_fail = 0;

static void check(bool cond, const std::string &name) {
  if (cond) {
    ++g_pass;
    std::cerr << "[PASS] " << name << std::endl;
  } else {
    ++g_fail;
    std::cerr << "[FAIL] " << name << std::endl;
  }
}

/* ------------------------------------------------------------------ */
/*  searchable_array_bag                                              */
/* ------------------------------------------------------------------ */

static void test_searchable_array_bag() {
  std::cerr << "--- searchable_array_bag ---" << std::endl;

  searchable_array_bag b;
  b.insert(10);
  b.insert(20);
  b.insert(30);
  check(b.has(10), "array_bag: has inserted value 10");
  check(b.has(20), "array_bag: has inserted value 20");
  check(b.has(30), "array_bag: has inserted value 30");
  check(!b.has(99), "array_bag: !has missing value 99");

  int arr[3] = {40, 50, 60};
  b.insert(arr, 3);
  check(b.has(40) && b.has(50) && b.has(60), "array_bag: insert(int *, int)");

  // copy constructor must do a deep copy
  searchable_array_bag copy(b);
  check(copy.has(10) && copy.has(60), "array_bag: copy constructor copies values");
  copy.insert(777);
  check(copy.has(777) && !b.has(777), "array_bag: copy is independent (deep)");

  // assignment operator must do a deep copy
  searchable_array_bag assigned;
  assigned = b;
  check(assigned.has(20) && assigned.has(50), "array_bag: assignment operator");
  assigned.insert(888);
  check(assigned.has(888) && !b.has(888), "array_bag: assignment is independent (deep)");

  // clear
  b.clear();
  check(!b.has(10) && !b.has(60), "array_bag: clear() empties bag");

  // polymorphism through the abstract searchable_bag interface
  searchable_bag *p = new searchable_array_bag();
  p->insert(5);
  check(p->has(5) && !p->has(6), "array_bag: polymorphic has() via searchable_bag*");
  p->print();
  delete p;
}

/* ------------------------------------------------------------------ */
/*  searchable_tree_bag                                               */
/* ------------------------------------------------------------------ */

static void test_searchable_tree_bag() {
  std::cerr << "--- searchable_tree_bag ---" << std::endl;

  searchable_tree_bag b;
  b.insert(50);
  b.insert(30);
  b.insert(70);
  b.insert(20);
  b.insert(40);
  check(b.has(50) && b.has(30) && b.has(70) && b.has(20) && b.has(40),
        "tree_bag: has all inserted values");
  check(!b.has(99) && !b.has(0), "tree_bag: !has missing values");

  // inserting a duplicate must not corrupt the tree
  b.insert(30);
  check(b.has(30), "tree_bag: duplicate insert keeps value");

  int arr[3] = {10, 60, 80};
  b.insert(arr, 3);
  check(b.has(10) && b.has(60) && b.has(80), "tree_bag: insert(int *, int)");

  // copy constructor must do a deep copy
  searchable_tree_bag copy(b);
  check(copy.has(50) && copy.has(80), "tree_bag: copy constructor copies values");
  copy.insert(999);
  check(copy.has(999) && !b.has(999), "tree_bag: copy is independent (deep)");

  // assignment operator must do a deep copy
  searchable_tree_bag assigned;
  assigned = b;
  check(assigned.has(20) && assigned.has(60), "tree_bag: assignment operator");
  assigned.insert(111);
  check(assigned.has(111) && !b.has(111), "tree_bag: assignment is independent (deep)");

  // clear
  b.clear();
  check(!b.has(50) && !b.has(20), "tree_bag: clear() empties bag");

  // polymorphism through the abstract searchable_bag interface
  searchable_bag *p = new searchable_tree_bag();
  p->insert(7);
  check(p->has(7) && !p->has(8), "tree_bag: polymorphic has() via searchable_bag*");
  p->print();
  delete p;
}

/* ------------------------------------------------------------------ */
/*  set                                                               */
/* ------------------------------------------------------------------ */

static void test_set() {
  std::cerr << "--- set ---" << std::endl;

  searchable_array_bag ab;
  set s(ab);
  s.insert(1);
  s.insert(2);
  s.insert(3);
  check(s.has(1) && s.has(2) && s.has(3), "set: has inserted values");
  check(!s.has(42), "set: !has missing value");

  // set semantics: re-inserting an existing element is a no-op
  s.insert(2);
  check(s.has(2), "set: duplicate insert keeps value");

  int arr[4] = {4, 5, 6, 7};
  s.insert(arr, 4);
  check(s.has(4) && s.has(7), "set: insert(int *, int)");

  // get_bag() exposes the underlying searchable_bag as const
  const searchable_bag &ref = s.get_bag();
  check(ref.has(1), "set: get_bag() exposes underlying bag");

  // the copy constructor shares the same underlying bag (reference member)
  set s2(s.get_bag());
  check(s2.has(1) && s2.has(7), "set: copy constructor shares underlying bag");
  s2.insert(100);
  check(s.has(100), "set: copy shares same bag (insert visible in original)");

  s.clear();
  check(!s.has(1) && !s.has(7), "set: clear() empties bag");

  // a set built on top of a tree bag must behave the same way
  searchable_tree_bag tb;
  set st(tb);
  st.insert(11);
  st.insert(22);
  check(st.has(11) && st.has(22) && !st.has(33), "set: works over a tree bag");
}

/* ------------------------------------------------------------------ */
/*  runner                                                            */
/* ------------------------------------------------------------------ */

static void run_tests() {
  std::cerr << "========== Polyset tests ==========" << std::endl;

  // The bag implementations are very chatty on std::cout (create/destroy
  // node messages, print output, ...). Silence std::cout while the tests
  // run so the PASS/FAIL report on std::cerr stays readable.
  std::ostringstream sink;
  std::streambuf *old_cout = std::cout.rdbuf(sink.rdbuf());

  test_searchable_array_bag();
  test_searchable_tree_bag();
  test_set();

  std::cout.rdbuf(old_cout); // restore std::cout

  std::cerr << "===================================" << std::endl;
  std::cerr << "PASSED: " << g_pass << "   FAILED: " << g_fail << std::endl;
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  run_tests();

  (void)argv;
  if (argc == 1)
    return 1;
  searchable_bag *t = new searchable_tree_bag;
  searchable_bag *a = new searchable_array_bag;

  for (int i = 1; i < argc; i++) {
    t->insert(atoi(argv[i]));
    a->insert(atoi(argv[i]));
  }
  t->print();
  a->print();

  for (int i = 1; i < argc; i++) {
    std::cout << t->has(atoi(argv[i])) << std::endl;
    std::cout << a->has(atoi(argv[i])) << std::endl;
    std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
    std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
  }

  t->clear();
  a->clear();

  const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
  tmp.print();
  tmp.has(1);

  set sa(*a);
  set st(*t);
  for (int i = 1; i < argc; i++) {
    st.insert(atoi(argv[i]));
    sa.insert(atoi(argv[i]));

    sa.has(atoi(argv[i]));
    sa.print();
    sa.get_bag().print();
    st.print();
    sa.clear();
    int array[4] = {1, 2, 3, 4};
    sa.insert(array, 4);
    std::cout << std::endl;
  }
  delete a;
  delete t;

  return g_fail == 0 ? 0 : 1;
}
