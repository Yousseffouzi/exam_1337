#include "bigint.hpp"
#include <iostream>

void check(const std::string& name, const bigint& got, const bigint& expected)
{
    if (got == expected)
        std::cout << "[PASS] " << name << '\n';
    else
        std::cout << "[FAIL] " << name
                  << " | Expected: " << expected
                  << " | Got: " << got << '\n';
}

int main()
{
    // Constructors
    check("Default constructor", bigint(), bigint("0"));
    check("Leading zeros", bigint("000123"), bigint("123"));
    check("Invalid string", bigint("12ab"), bigint("0"));

    // Addition
    check("0 + 0", bigint("0") + bigint("0"), bigint("0"));
    check("1 + 1", bigint("1") + bigint("1"), bigint("2"));
    check("999 + 1", bigint("999") + bigint("1"), bigint("1000"));
    check("12345 + 67890", bigint("12345") + bigint("67890"), bigint("80235"));

    // +=
    bigint a("50");
    a += bigint("25");
    check("operator+=", a, bigint("75"));

    // Prefix ++
    bigint b("9");
    ++b;
    check("Prefix ++", b, bigint("10"));

    // Postfix ++
    bigint c("9");
    bigint old = c++;
    check("Postfix return", old, bigint("9"));
    check("Postfix value", c, bigint("10"));

    // Left shift
    check("42 << 3", bigint("42") << 3, bigint("42000"));

    // Right shift
    check("1337 >> 2", bigint("1337") >> 2, bigint("13"));
    check("5 >> 10", bigint("5") >> 10, bigint("0"));

    // Comparisons
    std::cout << "\nComparison tests:\n";

    std::cout << ((bigint("5") > bigint("4")) ? "[PASS]\n" : "[FAIL]\n");
    std::cout << ((bigint("4") < bigint("5")) ? "[PASS]\n" : "[FAIL]\n");
    std::cout << ((bigint("5") >= bigint("5")) ? "[PASS]\n" : "[FAIL]\n");
    std::cout << ((bigint("5") <= bigint("5")) ? "[PASS]\n" : "[FAIL]\n");
    std::cout << ((bigint("5") == bigint("5")) ? "[PASS]\n" : "[FAIL]\n");
    std::cout << ((bigint("5") != bigint("6")) ? "[PASS]\n" : "[FAIL]\n");

    return 0;
}