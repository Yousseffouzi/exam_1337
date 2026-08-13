#include "BigInt.hpp"
#include <iostream>

static int passed = 0;
static int failed = 0;

static void check(const char *name, const bigint &got, const char *expected)
{
    if (got.getStr() == expected)
    {
        std::cout << "[OK]   " << name
                  << " -> " << got << std::endl;
        ++passed;
    }
    else
    {
        std::cout << "[FAIL] " << name
                  << " -> got: " << got
                  << " expected: " << expected << std::endl;
        ++failed;
    }
}

static void checkBool(const char *name, bool got, bool expected)
{
    if (got == expected)
    {
        std::cout << "[OK]   " << name << std::endl;
        ++passed;
    }
    else
    {
        std::cout << "[FAIL] " << name
                  << " -> got: " << got
                  << " expected: " << expected << std::endl;
        ++failed;
    }
}

int main()
{
    std::cout << "\n========== CONSTRUCTORS ==========\n";

    check("default constructor",
          bigint(), "0");

    check("unsigned constructor",
          bigint(42), "42");

    bigint a(123456789);
    bigint b(a);

    check("copy constructor",
          b, "123456789");

    bigint c;
    c = a;

    check("assignment operator",
          c, "123456789");

    c = c;

    check("self assignment",
          c, "123456789");


    std::cout << "\n========== ADDITION ==========\n";

    check("1 + 1",
          bigint(1) + bigint(1), "2");

    check("42 + 58",
          bigint(42) + bigint(58), "100");

    check("999 + 1",
          bigint(999) + bigint(1), "1000");

    check("9999 + 1",
          bigint(9999) + bigint(1), "10000");

    check("123456789 + 987654321",
          bigint(123456789) + bigint(987654321), "1111111110");

    check("999999999 + 999999999",
          bigint(999999999) + bigint(999999999), "1999999998");


    std::cout << "\n========== += ==========\n";

    bigint add(100);

    add += bigint(23);

    check("100 += 23",
          add, "123");

    add += bigint(877);

    check("123 += 877",
          add, "1000");


    std::cout << "\n========== PREFIX ++ ==========\n";

    bigint pre(999);

    ++pre;

    check("++999",
          pre, "1000");

    ++pre;

    check("++1000",
          pre, "1001");


    std::cout << "\n========== POSTFIX ++ ==========\n";

    bigint post(999);

    bigint old = post++;

    check("postfix returned value",
          old, "999");

    check("postfix incremented object",
          post, "1000");


    std::cout << "\n========== LEFT SHIFT ==========\n";

    check("42 << 0",
          bigint(42) << 0u, "42");

    check("42 << 1",
          bigint(42) << 1u, "420");

    check("42 << 3",
          bigint(42) << 3u, "42000");

    check("1337 << 2",
          bigint(1337) << 2u, "133700");

    check("1 << 10",
          bigint(1) << 10u, "10000000000");

    check("0 << 100",
          bigint(0) << 100u, "0");


    std::cout << "\n========== RIGHT SHIFT ==========\n";

    check("42 >> 0",
          bigint(42) >> 0u, "42");

    check("42 >> 1",
          bigint(42) >> 1u, "4");

    check("42 >> 2",
          bigint(42) >> 2u, "0");

    check("1337 >> 1",
          bigint(1337) >> 1u, "133");

    check("1337 >> 2",
          bigint(1337) >> 2u, "13");

    check("1337 >> 3",
          bigint(1337) >> 3u, "1");

    check("1337 >> 4",
          bigint(1337) >> 4u, "0");

    check("123456789 >> 5",
          bigint(123456789) >> 5u, "1234");

    check("123 >> 100",
          bigint(123) >> 100u, "0");


    std::cout << "\n========== <<= ==========\n";

    bigint leftAssign(42);

    leftAssign <<= 3u;

    check("42 <<= 3",
          leftAssign, "42000");

    leftAssign <<= 2u;

    check("42000 <<= 2",
          leftAssign, "4200000");


    std::cout << "\n========== >>= ==========\n";

    bigint rightAssign(4200000);

    rightAssign >>= 2u;

    check("4200000 >>= 2",
          rightAssign, "42000");

    rightAssign >>= 3u;

    check("42000 >>= 3",
          rightAssign, "42");

    rightAssign >>= 2u;

    check("42 >>= 2",
          rightAssign, "0");


    std::cout << "\n========== BIGINT SHIFT OPERAND ==========\n";

    bigint value(123456);
    bigint shift2(2);

    check("123456 << bigint(2)",
          value << shift2, "12345600");

    check("123456 >> bigint(2)",
          value >> shift2, "1234");

    bigint valueLeft(1234);
    bigint shift3(3);

    valueLeft <<= shift3;

    check("1234 <<= bigint(3)",
          valueLeft, "1234000");

    bigint valueRight(1234000);

    valueRight >>= shift3;

    check("1234000 >>= bigint(3)",
          valueRight, "1234");


    std::cout << "\n========== SHIFT OBJECT PRESERVATION ==========\n";

    bigint original(12345);

    bigint shiftedLeft = original << 3u;
    bigint shiftedRight = original >> 2u;

    check("original after <<",
          original, "12345");

    check("result of <<",
          shiftedLeft, "12345000");

    check("original after >>",
          original, "12345");

    check("result of >>",
          shiftedRight, "123");


    std::cout << "\n========== ZERO ==========\n";

    bigint zero(0);

    check("zero",
          zero, "0");

    check("zero + zero",
          zero + zero, "0");

    check("zero + 42",
          zero + bigint(42), "42");

    check("42 + zero",
          bigint(42) + zero, "42");

    check("zero << 10",
          zero << 10u, "0");

    check("zero >> 10",
          zero >> 10u, "0");


    std::cout << "\n========== COMPARISONS ==========\n";

    bigint ten(10);
    bigint twenty(20);
    bigint tenAgain(10);

    checkBool("10 < 20", ten < twenty, true);
    checkBool("20 > 10", twenty > ten, true);

    checkBool("10 <= 20", ten <= twenty, true);
    checkBool("20 >= 10", twenty >= ten, true);

    checkBool("10 == 10", ten == tenAgain, true);
    checkBool("10 != 20", ten != twenty, true);

    checkBool("10 <= 10", ten <= tenAgain, true);
    checkBool("10 >= 10", ten >= tenAgain, true);

    checkBool("10 not > 20", ten > twenty, false);
    checkBool("20 not < 10", twenty < ten, false);


    std::cout << "\n========== COMPARISON BY LENGTH ==========\n";

    checkBool("9 < 10",
              bigint(9) < bigint(10), true);

    checkBool("10 > 9",
              bigint(10) > bigint(9), true);

    checkBool("99 < 100",
              bigint(99) < bigint(100), true);

    checkBool("100 > 99",
              bigint(100) > bigint(99), true);


    std::cout << "\n========== COMPARISON SAME LENGTH ==========\n";

    checkBool("123 < 124",
              bigint(123) < bigint(124), true);

    checkBool("124 > 123",
              bigint(124) > bigint(123), true);

    checkBool("123 == 123",
              bigint(123) == bigint(123), true);

    checkBool("123 != 124",
              bigint(123) != bigint(124), true);


    std::cout << "\n========== COMPOUND OPERATIONS ==========\n";

    bigint compound(42);

    compound <<= 3u;
    compound += bigint(1337);
    compound >>= 2u;
    ++compound;

    check("42 <<= 3, += 1337, >>= 2, ++",
          compound, "1084");


    std::cout << "\n========== CHAINING ==========\n";

    bigint chain =
        ((bigint(10) + bigint(20)) << 2u) >> 1u;

    check("(10 + 20) << 2 >> 1",
          chain, "150");


    std::cout << "\n========== LARGE NUMBER ==========\n";

    bigint huge(1);

    huge <<= 100u;

    check("1 << 100 length",
          bigint(huge.getStr().length()), "101");

    check("1 << 100",
          huge,
          "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");


    std::cout << "\n========== LARGE ADDITION ==========\n";

    bigint big1(999999999);
    bigint big2(999999999);

    check("999999999 + 999999999",
          big1 + big2, "1999999998");


    std::cout << "\n========== OUTPUT OPERATOR ==========\n";

    std::cout << "operator<< output: ";
    std::cout << bigint(123456789) << std::endl;

    check("getStr()",
          bigint(123456789), "123456789");


    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "              FINAL RESULT\n";
    std::cout << "========================================\n";
    std::cout << "Total  : " << passed + failed << std::endl;
    std::cout << "Passed : " << passed << std::endl;
    std::cout << "Failed : " << failed << std::endl;
    std::cout << "========================================\n";

    if (failed == 0)
        std::cout << "        ALL TESTS PASSED!\n";
    else
        std::cout << "        SOME TESTS FAILED!\n";

    return failed == 0 ? 0 : 1;
}
