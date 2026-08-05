#include "BigInt.hpp"

// int main()
// {
//     BigInt a("42");
//     BigInt b(21), c, d(1337), e(d);

//     std::cout << "a = " << a << std::endl;
//     std::cout << "b = " << b << std::endl;
//     std::cout << "c = " << c << std::endl;
//     std::cout << "d = " << d << std::endl;
//     std::cout << "e = " << e << std::endl;

//     std::cout << "a + b = " << a + b << std::endl;
//     std::cout << "(c += a) = " << (c += a) << std::endl;

//     std::cout << "b = " << b << std::endl;
//     std::cout << "++b = " << ++b << std::endl;
//     std::cout << "b++ = " << b++ << std::endl;

//     std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
//     std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
//     std::cout << "(d >>= 2) = " << (d >>= (const BigInt)2) << std::endl;

//     std::cout << "a =" << a << std::endl;
//     std::cout << "d =" << d << std::endl;

//     std::cout << "(d < a) = " << (d < a) << std::endl;
//     std::cout << "(d <= a) = " << (d <= a) << std::endl;
//     std::cout << "(d > a) = " << (d > a) << std::endl;
//     std::cout << "(d >= a) = " << (d >= a) << std::endl;
//     std::cout << "(d == a) = " << (d == a) << std::endl;
//     std::cout << "(d != a) = " << (d != a) << std::endl;
// }


static int passed = 0;
static int failed = 0;

void check(const std::string &name, const BigInt &got, const BigInt &expected)
{
    if (got == expected)
    {
        ++passed;
        std::cout << "[PASS] " << name << '\n';
    }
    else
    {
        ++failed;
        std::cout << "[FAIL] " << name
                  << "\n  Expected: " << expected
                  << "\n  Got     : " << got << "\n\n";
    }
}

void checkBool(const std::string &name, bool got, bool expected)
{
    if (got == expected)
    {
        ++passed;
        std::cout << "[PASS] " << name << '\n';
    }
    else
    {
        ++failed;
        std::cout << "[FAIL] " << name
                  << "\n  Expected: " << expected
                  << "\n  Got     : " << got << "\n\n";
    }
}

int main()
{
    // ================= Constructors =================
    check("Default constructor", BigInt(), BigInt("0"));
    check("Unsigned long constructor", BigInt(42), BigInt("42"));
    check("Leading zeros", BigInt("00000123"), BigInt("123"));
    check("Only zeros", BigInt("000000"), BigInt("0"));
    check("Invalid string", BigInt("12ab"), BigInt("0"));
    check("Empty string", BigInt(""), BigInt("0"));

    // ================= Leading Zero Tests =================
    check("0000", BigInt("0000"), BigInt("0"));
    check("000000", BigInt("000000"), BigInt("0"));
    check("000123", BigInt("000123"), BigInt("123"));
    check("0012300", BigInt("0012300"), BigInt("12300"));
    check("000000001", BigInt("000000001"), BigInt("1"));

    // ================= Copy / Assignment =================
    BigInt a("123456");
    BigInt b(a);
    check("Copy constructor", b, BigInt("123456"));

    BigInt c;
    c = a;
    check("Assignment", c, BigInt("123456"));

    c = c;
    check("Self assignment", c, BigInt("123456"));

    // ================= Addition =================
    check("0 + 0", BigInt("0") + BigInt("0"), BigInt("0"));
    check("1 + 1", BigInt("1") + BigInt("1"), BigInt("2"));
    check("9 + 1", BigInt("9") + BigInt("1"), BigInt("10"));
    check("99 + 1", BigInt("99") + BigInt("1"), BigInt("100"));
    check("999 + 1", BigInt("999") + BigInt("1"), BigInt("1000"));
    check("12345 + 67890", BigInt("12345") + BigInt("67890"), BigInt("80235"));
    check("Large addition",
          BigInt("999999999999999999999999") + BigInt("1"),
          BigInt("1000000000000000000000000"));

    // ================= Addition + Leading Zeros =================
    check("0005 + 0007", BigInt("0005") + BigInt("0007"), BigInt("12"));
    check("0000 + 0000", BigInt("0000") + BigInt("0000"), BigInt("0"));
    check("000999 + 1", BigInt("000999") + BigInt("1"), BigInt("1000"));
    check("000123 + 000877", BigInt("000123") + BigInt("000877"), BigInt("1000"));

    // ================= += =================
    BigInt d("50");
    d += BigInt("25");
    check("operator+=", d, BigInt("75"));

    d += BigInt("0");
    check("+= zero", d, BigInt("75"));

    // ================= Prefix ++ =================
    BigInt e("9");
    ++e;
    check("Prefix ++", e, BigInt("10"));

    BigInt f("999");
    ++f;
    check("Prefix ++ carry", f, BigInt("1000"));

    // ================= Postfix ++ =================
    BigInt g("9");
    BigInt old = g++;
    check("Postfix returned value", old, BigInt("9"));
    check("Postfix object value", g, BigInt("10"));

    // ================= Left Shift =================
    check("42 << 0", BigInt("42") << 0, BigInt("42"));
    check("42 << 3", BigInt("42") << 3, BigInt("42000"));
    check("0 << 5", BigInt("0") << 5, BigInt("0"));

    // ================= Left Shift + Leading Zeros =================
    check("00042 << 3", BigInt("00042") << 3, BigInt("42000"));
    check("0000 << 5", BigInt("0000") << 5, BigInt("0"));

    // ================= Right Shift =================
    check("1337 >> 2", BigInt("1337") >> 2, BigInt("13"));
    check("123 >> 0", BigInt("123") >> 0, BigInt("123"));
    check("123 >> 3", BigInt("123") >> 3, BigInt("0"));
    check("123 >> 10", BigInt("123") >> 10, BigInt("0"));

    // ================= Right Shift + Leading Zeros =================
    check("00012345 >> 2", BigInt("00012345") >> 2, BigInt("123"));
    check("0000 >> 3", BigInt("0000") >> 3, BigInt("0"));
    check("000123 >> 10", BigInt("000123") >> 10, BigInt("0"));

    // ================= Shift by BigInt =================
    check("42 << BigInt(2)", BigInt("42") << BigInt("2"), BigInt("4200"));
    check("12345 >> BigInt(3)", BigInt("12345") >> BigInt("3"), BigInt("12"));

    // ================= <<= =================
    BigInt h("42");
    h <<= 3;
    check("operator<<=", h, BigInt("42000"));

    BigInt i("0");
    i <<= 5;
    check("operator<<= zero", i, BigInt("0"));

    // ================= >>= =================
    BigInt j("12345");
    j >>= 2;
    check("operator>>=", j, BigInt("123"));

    BigInt k("5");
    k >>= 10;
    check("operator>>= to zero", k, BigInt("0"));

    // ================= Comparisons =================
    checkBool("5 == 5", BigInt("5") == BigInt("5"), true);
    checkBool("5 == 6", BigInt("5") == BigInt("6"), false);

    checkBool("5 != 6", BigInt("5") != BigInt("6"), true);
    checkBool("5 != 5", BigInt("5") != BigInt("5"), false);

    checkBool("5 < 6", BigInt("5") < BigInt("6"), true);
    checkBool("6 < 5", BigInt("6") < BigInt("5"), false);
    checkBool("5 < 5", BigInt("5") < BigInt("5"), false);

    checkBool("6 > 5", BigInt("6") > BigInt("5"), true);
    checkBool("5 > 6", BigInt("5") > BigInt("6"), false);
    checkBool("5 > 5", BigInt("5") > BigInt("5"), false);

    checkBool("5 <= 5", BigInt("5") <= BigInt("5"), true);
    checkBool("5 <= 6", BigInt("5") <= BigInt("6"), true);
    checkBool("6 <= 5", BigInt("6") <= BigInt("5"), false);

    checkBool("5 >= 5", BigInt("5") >= BigInt("5"), true);
    checkBool("6 >= 5", BigInt("6") >= BigInt("5"), true);
    checkBool("5 >= 6", BigInt("5") >= BigInt("6"), false);

    // ================= Different Lengths =================
    checkBool("999 < 1000", BigInt("999") < BigInt("1000"), true);
    checkBool("1000 > 999", BigInt("1000") > BigInt("999"), true);
    checkBool("1000 >= 999", BigInt("1000") >= BigInt("999"), true);
    checkBool("999 <= 1000", BigInt("999") <= BigInt("1000"), true);

    // ================= Same Lengths =================
    checkBool("1234 < 1235", BigInt("1234") < BigInt("1235"), true);
    checkBool("1235 > 1234", BigInt("1235") > BigInt("1234"), true);
    checkBool("1234 <= 1234", BigInt("1234") <= BigInt("1234"), true);
    checkBool("1234 >= 1234", BigInt("1234") >= BigInt("1234"), true);

    // ================= Comparisons + Leading Zeros =================
    checkBool("0005 == 5", BigInt("0005") == BigInt("5"), true);
    checkBool("0005 != 5", BigInt("0005") != BigInt("5"), false);
    checkBool("0005 < 6", BigInt("0005") < BigInt("6"), true);
    checkBool("0006 > 5", BigInt("0006") > BigInt("5"), true);
    checkBool("0000 == 0", BigInt("0000") == BigInt("0"), true);
    checkBool("0000 <= 0", BigInt("0000") <= BigInt("0"), true);
    checkBool("0000 >= 0", BigInt("0000") >= BigInt("0"), true);
    checkBool("000123 > 000122", BigInt("000123") > BigInt("000122"), true);
    checkBool("000122 < 000123", BigInt("000122") < BigInt("000123"), true);

    // ================= Summary =================
    std::cout << "\n========================================\n";
    std::cout << "Total Tests : " << passed + failed << '\n';
    std::cout << "Passed      : " << passed << '\n';
    std::cout << "Failed      : " << failed << '\n';

    if (failed == 0)
        std::cout << "\n🎉 ALL TESTS PASSED!\n";
    else
        std::cout << "\n❌ Some tests failed.\n";

    std::cout << "========================================\n";

    return failed == 0 ? 0 : 1;
}

