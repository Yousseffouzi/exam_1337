#include "vect2.hpp"
#include <iostream>
#include <sstream>

/* ************************************************************************** */
/*  Tiny unit-test harness (no external libraries needed)                     */
/* ************************************************************************** */

static int g_pass = 0;
static int g_fail = 0;

static void check(const char *name, bool cond)
{
    if (cond)
    {
        std::cout << "[\033[32mPASS\033[0m] " << name << std::endl;
        g_pass++;
    }
    else
    {
        std::cout << "[\033[31mFAIL\033[0m] " << name << std::endl;
        g_fail++;
    }
}

// Helper: does a vector equal the pair (a, b) ?
static bool eq(const vect2 &v, int a, int b)
{
    return v[0] == a && v[1] == b;
}

/* ************************************************************************** */
/*  Tests                                                                     */
/* ************************************************************************** */

static void test_constructors()
{
    vect2 v1;            // default -> 0, 0
    vect2 v2(1, 2);      // params  -> 1, 2
    const vect2 v3(v2);  // copy    -> 1, 2
    vect2 v4 = v2;       // copy    -> 1, 2

    check("default ctor is {0, 0}", eq(v1, 0, 0));
    check("param ctor {1, 2}", eq(v2, 1, 2));
    check("copy ctor (const) {1, 2}", eq(v3, 1, 2));
    check("copy-init ctor {1, 2}", eq(v4, 1, 2));
}

static void test_assignment()
{
    vect2 a(5, 9);
    vect2 b;

    b = a;
    check("operator= copies values", eq(b, 5, 9));

    // self assignment must be safe
    a = a;
    check("operator= self-assign safe", eq(a, 5, 9));

    // chained assignment
    vect2 c;
    c = b = a;
    check("operator= chaining", eq(c, 5, 9) && eq(b, 5, 9));
}

static void test_subscript()
{
    vect2 v(7, 8);

    check("operator[] read index 0", v[0] == 7);
    check("operator[] read index 1", v[1] == 8);

    v[0] = 42;
    v[1] = -3;
    check("operator[] write index 0", v[0] == 42);
    check("operator[] write index 1", v[1] == -3);

    const vect2 cv(11, 12);
    check("const operator[] read", cv[0] == 11 && cv[1] == 12);
}

static void test_increment()
{
    vect2 v(1, 2);

    vect2 old = v++;          // post: returns old, then increments
    check("post-increment returns old value", eq(old, 1, 2));
    check("post-increment modifies object", eq(v, 2, 3));

    vect2 res = ++v;          // pre: increments, returns new
    check("pre-increment returns new value", eq(res, 3, 4));
    check("pre-increment modifies object", eq(v, 3, 4));
}

static void test_decrement()
{
    vect2 v(3, 4);

    vect2 old = v--;          // post: returns old, then decrements
    check("post-decrement returns old value", eq(old, 3, 4));
    check("post-decrement modifies object", eq(v, 2, 3));

    vect2 res = --v;          // pre: decrements, returns new
    check("pre-decrement returns new value", eq(res, 1, 2));
    check("pre-decrement modifies object", eq(v, 1, 2));
}

static void test_compound_assign()
{
    vect2 a(2, 4);
    vect2 b(1, 3);

    a += b;
    check("operator+= adds component-wise", eq(a, 3, 7));

    a -= b;
    check("operator-= subtracts component-wise", eq(a, 2, 4));

    a *= 3;
    check("operator*= scalar multiplies", eq(a, 6, 12));

    // chained: x += y += z  (subject: v2 += v2 += v3)
    vect2 x(9, 18);
    vect2 z(1, 2);
    x += x += z;             // inner: x -> (10,20); outer: x += x -> (20,40)
    check("operator+= chaining (x += x += z)", eq(x, 20, 40));
}

static void test_arithmetic()
{
    vect2 a(3, 6);
    vect2 b(1, 2);

    check("operator+ {3,6}+{1,2}", eq(a + b, 4, 8));
    check("operator- {3,6}-{1,2}", eq(a - b, 2, 4));
    check("unary operator- negates", eq(-a, -3, -6));

    // originals must be unchanged by + - (they return copies)
    check("operator+ leaves operands intact", eq(a, 3, 6) && eq(b, 1, 2));
}

static void test_scalar_mul()
{
    vect2 v(2, 2);

    // subject example: vect2(2,2) * 2 == vect2(4,4)
    check("v * scalar (member)", v * 2 == vect2(4, 4));
    check("scalar * v (free function)", 3 * v == vect2(6, 6));
    check("scalar mul leaves operand intact", eq(v, 2, 2));

    // combined expression: v3 + v3 * 2 -> (1,2)+(2,4) = (3,6)
    const vect2 v3(1, 2);
    check("v3 + v3 * 2 == {3,6}", v3 + v3 * 2 == vect2(3, 6));
}

static void test_comparison()
{
    vect2 a(1, 2);
    vect2 b(1, 2);
    vect2 c(9, 9);

    check("operator== equal vectors", (a == b) == true);
    check("operator== self", (a == a) == true);
    check("operator== different vectors", (a == c) == false);
    check("operator!= equal vectors", (a != b) == false);
    check("operator!= different vectors", (a != c) == true);
}

static void test_output()
{
    vect2 v(3, -7);
    std::ostringstream oss;
    oss << v;
    check("operator<< prints \"{x, y}\"", oss.str() == "{3, -7}");

    // must match the manual form required by the subject
    std::ostringstream manual;
    manual << "{" << v[0] << ", " << v[1] << "}";
    check("operator<< matches manual form", oss.str() == manual.str());
}

// Replays the exact scenario from subject.txt and checks the final state.
static void test_subject_scenario()
{
    vect2 v1;            // 0, 0
    vect2 v2(1, 2);      // 1, 2
    const vect2 v3(v2);  // 1, 2
    vect2 v4 = v2;       // 1, 2

    v4++;                // 2, 3
    ++v4;                // 3, 4
    v4--;                // 2, 3
    --v4;                // 1, 2
    check("scenario: v4 back to {1,2}", eq(v4, 1, 2));

    v2 += v3;            // 2, 4
    v1 -= v2;            // -2, -4
    v2 = v3 + v3 * 2;    // 3, 6
    v2 = 3 * v2;         // 9, 18
    v2 += v2 += v3;      // 20, 40
    v1 *= 42;            // -84, -168
    v1 = v1 - v1 + v1;   // -84, -168

    check("scenario: v1 == {-84,-168}", eq(v1, -84, -168));
    check("scenario: v2 == {20,40}", eq(v2, 20, 40));
    check("scenario: -v2 == {-20,-40}", eq(-v2, -20, -40));

    v1[1] = 12;          // -84, 12
    check("scenario: v1 after v1[1]=12 -> {-84,12}", eq(v1, -84, 12));
    check("scenario: v3[1] == 2", v3[1] == 2);

    check("scenario: v1 == v3 is false", (v1 == v3) == false);
    check("scenario: v1 == v1 is true", (v1 == v1) == true);
    check("scenario: v1 != v3 is true", (v1 != v3) == true);
    check("scenario: v1 != v1 is false", (v1 != v1) == false);
}

static int run_all_tests()
{
    test_constructors();
    test_assignment();
    test_subscript();
    test_increment();
    test_decrement();
    test_compound_assign();
    test_arithmetic();
    test_scalar_mul();
    test_comparison();
    test_output();
    test_subject_scenario();

    std::cout << "\n----------------------------------------\n";
    std::cout << "Total: " << (g_pass + g_fail)
              << " | Passed: " << g_pass
              << " | Failed: " << g_fail << std::endl;
    return (g_fail == 0 ? 0 : 1);
}

int main()
{
    // vect2 v1; // 0, 0
    // vect2 v2(1, 2); // 1, 2
    // const vect2 v3(v2); // 1, 2
    // vect2 v4 = v2; // 1, 2

    // std::cout << "v1: " << v1 << std::endl;
    // std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl;
    // std::cout << "v2: " << v2 << std::endl;
    // std::cout << "v3: " << v3 << std::endl;
    // std::cout << "v4: " << v4 << std::endl;
    // std::cout << v4++ << std::endl; // 1, 2
    // std::cout << ++v4 << std::endl; // 3, 4
    // std::cout << v4-- << std::endl; // 3, 4
    // std::cout << --v4 << std::endl; // 1, 2
    // v2 += v3; // 2, 4
    // v1 -= v2; // -2, -4
    // v2 = v3 + v3 *2; // 3, 6
    // v2 = 3 * v2; // 9, 18
    // v2 += v2 += v3; // 20, 40
    // v1 *= 42; // -84, -168
    // v1 = v1 - v1 +v1;
    // std::cout << "v1: " << v1 << std::endl;
    // std::cout << "v2: " << v2 << std::endl;
    // std::cout << "-v2: " << -v2 << std::endl;
    // std::cout << "v1[1]: " << v1[1] << std::endl;
    // v1[1] = 12;
    // std::cout << "v1[1]: " << v1[1] << std::endl;
    // std::cout << "v3[1]: " << v3[1] << std::endl;
    // std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
    // std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
    // std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
    // std::cout << "v1 != v1: " << (v1 != v1) << std::endl;

    return (run_all_tests());
}
