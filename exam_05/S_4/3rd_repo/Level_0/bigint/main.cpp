#include "BigInt.hpp"
#include <iostream>
#include <cassert>

int main()
{
    std::cout << "===== BigInt FULL TEST =====" << std::endl;

    // --- Constructors ---
    BigInt a;                        // default constructor
    BigInt b(12345);                 // from unsigned int
    BigInt c("67890");               // from string
    BigInt d("0000123");             // with leading zeros
    BigInt e("abc");                 // invalid input

    std::cout << "a = " << a << " (default)" << std::endl;
    std::cout << "b = " << b << " (from unsigned int)" << std::endl;
    std::cout << "c = " << c << " (from string)" << std::endl;
    std::cout << "d = " << d << " (leading zeros removed)" << std::endl;
    std::cout << "e = " << e << " (invalid string → 0)" << std::endl;

    assert(a == BigInt("0"));
    assert(b == BigInt("12345"));
    assert(c == BigInt("67890"));
    assert(d == BigInt("123"));
    assert(e == BigInt("0"));
    std::cout << "Constructors ✅" << std::endl;

    // --- Addition ---
    BigInt x("999");
    BigInt y("1");
    BigInt z = x + y;                // 999 + 1 = 1000
    std::cout << "999 + 1 = " << z << std::endl;
    assert(z == BigInt("1000"));

    BigInt s1("123456789");
    BigInt s2("987654321");
    BigInt s3 = s1 + s2;             // 123456789 + 987654321 = 1111111110
    std::cout << "123456789 + 987654321 = " << s3 << std::endl;
    assert(s3 == BigInt("1111111110"));
    std::cout << "Addition ✅" << std::endl;

    // --- Operator += ---
    BigInt addEq("50");
    addEq += BigInt("25");
    std::cout << "50 += 25 → " << addEq << std::endl;
    assert(addEq == BigInt("75"));
    std::cout << "Operator += ✅" << std::endl;

    // --- Comparisons ---
    BigInt p("123"), q("124"), r("123");
    assert(p == r);
    assert(p != q);
    assert(p < q);
    assert(q > p);
    assert(p <= r);
    assert(q >= p);
    std::cout << "Comparisons ✅" << std::endl;

    // --- Shift operators (unsigned int) ---
    BigInt sft1("123");
    BigInt sft2 = sft1 << 2;         // multiply by 100
    BigInt sft3 = sft1 >> 1;         // divide by 10
    std::cout << "123 << 2 = " << sft2 << std::endl;
    std::cout << "123 >> 1 = " << sft3 << std::endl;
    assert(sft2 == BigInt("12300"));
    assert(sft3 == BigInt("12"));
    std::cout << "Shift operators ✅" << std::endl;

    // --- Compound shifts (unsigned int) ---
    BigInt shiftEq("1234");
    shiftEq <<= 2;                   // multiply by 100
    std::cout << "1234 <<= 2 → " << shiftEq << std::endl;
    shiftEq >>= 3;                   // divide by 1000
    std::cout << "then >>= 3 → " << shiftEq << std::endl;
    assert(shiftEq == BigInt("123"));
    std::cout << "Compound shifts ✅" << std::endl;

    // --- Shift operators (const BigInt&) ---
    BigInt shBig("12345");
    BigInt two("2");
    std::cout << "shBig <<= (const BigInt)2 → " << (shBig <<= two) << std::endl;

    BigInt shBig2("12345");
    std::cout << "shBig2 >>= (const BigInt)2 → " << (shBig2 >>= two) << std::endl;
    std::cout << "BigInt shift by BigInt ✅" << std::endl;

    // --- Increment operators ---
    BigInt inc("9");
    std::cout << "++9 → " << ++inc << std::endl; // prefix (++9 = 10)
    assert(inc == BigInt("10"));

    BigInt post("19");
    BigInt old = post++;
    std::cout << "post++: old=" << old << ", new=" << post << std::endl;
    assert(old == BigInt("19"));
    assert(post == BigInt("20"));
    std::cout << "Increment operators ✅" << std::endl;

    // --- Zero handling ---
    BigInt zero("0");
    BigInt sum = zero + BigInt("123");
    std::cout << "0 + 123 = " << sum << std::endl;
    assert(sum == BigInt("123"));
    assert((zero << 5) == BigInt("0"));
    assert((zero >> 5) == BigInt("0"));
    std::cout << "Zero handling ✅" << std::endl;

    // --- Leading zero cleanup ---
    BigInt leading("00000123");
    BigInt clean = leading + BigInt("0");
    std::cout << "00000123 + 0 = " << clean << std::endl;
    assert(clean == BigInt("123"));
    std::cout << "Leading zero cleanup ✅" << std::endl;

    // --- Stress test ---
    BigInt counter("0");
    for (int i = 0; i < 50; i++)
        ++counter;
    std::cout << "Incremented 50 times: " << counter << std::endl;
    assert(counter == BigInt("50"));
    std::cout << "Stress test ✅" << std::endl;

    std::cout << "\nAll tests passed 🎯" << std::endl;
    return 0;
}

