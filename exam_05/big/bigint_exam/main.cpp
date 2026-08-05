// // #include "bigint.hpp"

// // int main()
// // {
// // 	bigint a; // Default
// // 	bigint b(123456);
// // 	bigint c("78901234567890");
// // 	bigint d("0000012345"); // Leading zeros
// // 	bigint e("abc123");		  // Invalid string
// // 	bigint f(1);
// // 	bigint xs(100);

// // 	std::cout << "Constructors:\n";
// // 	std::cout << "a (default): " << a << "\n";
// // 	std::cout << "b (from int): " << b << "\n";
// // 	std::cout << "c (from string): " << c << "\n";
// // 	std::cout << "d (leading zeros): " << d << "\n";
// // 	std::cout << "e (invalid string): " << e << "\n";
// // 	std::cout << "f (from 0): " << f << "\n\n";

// // 	// Test addition
// // 	std::cout << "Addition:\n";
// // 	std::cout << b << " + " << d << " = " << (b + d) << "\n";
// // 	bigint g = c + b;
// // 	std::cout << c << " + " << b << " = " << g << "\n";
// // 	bigint h("999");
// // 	std::cout << h << " + 1 = " << (h + bigint(1)) << "\n\n";

// // 	// Test +=
// // 	std::cout << "Operator += :\n";
// // 	bigint x("1000");
// // 	x += bigint("2000");
// // 	std::cout << "1000 += 2000: " << x << "\n\n";

// // 	// Test comparison
// // 	std::cout << "Comparison:\n";
// // 	std::cout << "Is " << b << " == " << d << "? " << (b == d ? "yes" : "no") << "\n";
// // 	std::cout << "Is " << f << " == " << xs << "? " << (f == xs ? "yes" : "no") << "\n";
// // 	std::cout << "Is " << b << " != " << d << "? " << (b != d ? "yes" : "no") << "\n";
// // 	std::cout << "Is " << b << " < " << d << "? " << (b < d ? "yes" : "no") << "\n";
// // 	std::cout << "Is " << b << " > " << d << "? " << (b > d ? "yes" : "no") << "\n";
// // 	std::cout << "Is " << b << " <= " << d << "? " << (b <= d ? "yes" : "no") << "\n";
// // 	std::cout << "Is " << b << " >= " << d << "? " << (b >= d ? "yes" : "no") << "\n\n";

// // 	// Test digit left shift
// // 	std::cout << "Digit shift left:\n";
// // 	bigint y("12345");
// // 	std::cout << y << " << 3 = " << (y << 3) << "\n";
// // 	std::cout << y << " << 0 = " << (y << 0) << "\n";
// // 	std::cout << "0 << 10 = " << (bigint(0) << 10) << "\n\n";

// // 	// Test digit right shift
// // 	std::cout << "Digit shift right:\n";
// // 	std::cout << y << " >> 2 = " << (y >> 2) << "\n";
// // 	std::cout << y << " >> 10 = " << (y >> 10) << "\n";
// // 	std::cout << y << " >> 0 = " << (y >> 0) << "\n\n";

// // 	// Test <<= and >>=
// // 	std::cout << "Operator <<= and >>= :\n";
// // 	bigint z("98765");
// // 	z <<= 2;
// // 	std::cout << "98765 <<= 2: " << z << "\n";
// // 	z >>= 4;
// // 	std::cout << "(previous result) >>= 4: " << z << "\n\n";

// // 	// Test <<+ and >>+
// // 	std::cout << "Operator <<+ and >>+ :\n";
// // 	bigint m("13");
// // 	std::cout << m << " <<+ 2: " << (m << +2) << "\n";
// // 	std::cout << m << " >>+ 1: " << (m >> +1) << "\n\n";

// // 	// Test pre-increment and post-increment
// // 	std::cout << "Pre-increment and post-increment:\n";
// // 	bigint w("99");
// // 	std::cout << "Original w: " << w << "\n";
// // 	std::cout << "w++: " << w++ << "\n";
// // 	std::cout << "After w++: " << w << "\n";
// // 	std::cout << "++w: " << ++w << "\n";
// // 	std::cout << "After ++w: " << w << "\n";

// // 	// Edge test: huge shift right
// // 	std::cout << "\nEdge case: huge shift right\n";
// // 	bigint edge("123456789");
// // 	std::cout << edge << " >> 100 = " << (edge >> 100) << "\n";

// // 	return 0;
// // }

// #include "bigint.hpp"
// #include <iostream>
// #include <sstream>
// #include <string>

// static int g_pass = 0;
// static int g_fail = 0;

// static void check(const std::string& name,
//                   const std::string& got,
//                   const std::string& expected)
// {
//     if (got == expected)
//     {
//         std::cout << "\033[32m[PASS]\033[0m " << name << "  => " << got << std::endl;
//         ++g_pass;
//     }
//     else
//     {
//         std::cout << "\033[31m[FAIL]\033[0m " << name
//                   << "  expected \"" << expected << "\" got \"" << got << "\""
//                   << std::endl;
//         ++g_fail;
//     }
// }

// void test_constructors()
// {
//     std::cout << "\n=== constructors ===" << std::endl;
//     check("default ctor", bigint().toString(), "0");
//     check("int ctor",     bigint(42).toString(), "42");
//     check("string ctor",  bigint(std::string("1337")).toString(), "1337");

//     bigint a(42);
//     check("copy ctor",    bigint(a).toString(), "42");

//     std::stringstream os;
//     os << a;
//     check("operator<< ostream", os.str(), "42");
// }

// void test_plus()
// {
//     std::cout << "\n=== operator+ ===" << std::endl;
//     check("28 + 1337",      (bigint(28) + bigint(1337)).toString(), "1365");
//     check("carry 999 + 1",  (bigint(999) + bigint(1)).toString(),   "1000");
//     check("diff len 5+12345",(bigint(5) + bigint(12345)).toString(),"12350");

//     const bigint a(42);
//     bigint b(28);
//     check("const + nonconst", (a + b).toString(), "70");

//     // identities with zero
//     check("0 + 0",           (bigint(0) + bigint(0)).toString(),     "0");
//     check("0 + 42",          (bigint(0) + bigint(42)).toString(),    "42");
//     check("42 + 0",          (bigint(42) + bigint(0)).toString(),    "42");

//     // single digit / small carries
//     check("5 + 5",           (bigint(5) + bigint(5)).toString(),     "10");
//     check("7 + 8",           (bigint(7) + bigint(8)).toString(),     "15");
//     check("50 + 50",         (bigint(50) + bigint(50)).toString(),   "100");

//     // long carry chains
//     check("1 + 9999",        (bigint(1) + bigint(9999)).toString(),  "10000");
//     check("999999 + 1",      (bigint(999999) + bigint(1)).toString(),"1000000");
//     check("12345 + 54321",   (bigint(12345) + bigint(54321)).toString(), "66666");

//     // commutativity (a+b == b+a)
//     check("28 + 1337 (comm)",(bigint(1337) + bigint(28)).toString(), "1365");

//     // chained additions
//     check("1 + 2 + 3",       (bigint(1) + bigint(2) + bigint(3)).toString(), "6");

//     // int implicitly converted to bigint on the right-hand side
//     check("bigint(10) + 5",  (bigint(10) + 5).toString(),            "15");

//     check("big string add",
//           (bigint(std::string("99999999999999999999")) + bigint(1)).toString(),
//           "100000000000000000000");

//     check("big + big",
//           (bigint(std::string("123456789012345678901234567890"))
//            + bigint(std::string("987654321098765432109876543210"))).toString(),
//           "1111111110111111111011111111100");
// }

// //---- uncomment this function AND its call in main() once operator++ works ----
// void test_increment()
// {
//     std::cout << "\n=== operator++ ===" << std::endl;
//     bigint b(28);
//     check("++b returns",    (++b).toString(), "29");
//     check("b after ++b",    b.toString(),     "29");

//     bigint c(28);
//     check("c++ returns old",(c++).toString(), "28");
//     check("c after c++",    c.toString(),     "29");

//     check("++ carry 9->10", (++bigint(9)).toString(), "10");
// }


// //---- uncomment once operator+= works ----
// void test_plus_eq()
// {
//     std::cout << "\n=== operator+= ===" << std::endl;
//     bigint c;            // 0
//     bigint a(42);
//     check("(c += 42) returns", (c += a).toString(), "42");
//     check("c after +=",        c.toString(),        "42");

//     bigint x(1337);
//     x += bigint(63);
//     check("1337 += 63",        x.toString(),        "1400");
// }


// // ---- digit shift in base 10:  << appends zeros (x*10^n), >> drops digits (x/10^n) ----
// void test_shift()
// {
//     std::cout << "\n=== digit shift  << >> <<= >>= ===" << std::endl;
//     // <<  (subject: 42 << 3 == 42000)
//     check("42 << 3",        (bigint(0) << 7).toString(),       "0");
//     check("28 << 10",       (bigint(28) << 10).toString(),      "280000000000");
//     check("99 << 0",        (bigint(99) << 0).toString(),       "99");

//     // >>  (subject: 1337 >> 2 == 13)
//     check("1337 >> 2",      (bigint(1337) >> 2).toString(),     "13");
//     check("123456 >> 3",    (bigint(123456) >> 3).toString(),   "123");

//     // combined with +
//     bigint b(28);
//     check("(b << 10) + 42", ((b << 10) + 42).toString(),        "280000000042");

//     // <<= mutates in place
//     bigint d(1337);
//     check("(d <<= 4)",      (d <<= 4).toString(),               "13370000");
//     check("d after <<=",    d.toString(),                       "13370000");

//     // >>= mutates in place
//     bigint e(13370000);
//     check("(e >>= 4)",      (e >>= 4).toString(),               "1337");
// }


// //---- uncomment once the comparison operators work ----
// void test_compare()
// {
//     std::cout << "\n=== comparisons ===" << std::endl;
//     bigint a(42);
//     bigint d(1337);
//     check("1337 <  42", (d <  a) ? "true" : "false", "false");
//     check("1337 <= 42", (d <= a) ? "true" : "false", "false");
//     check("1337 >  42", (d >  a) ? "true" : "false", "true");
//     check("1337 >= 42", (d >= a) ? "true" : "false", "true");
//     check("1337 == 42", (d == a) ? "true" : "false", "false");
//     check("1337 != 42", (d != a) ? "true" : "false", "true");
//     check("42 == 42",   (bigint(42) == a) ? "true" : "false", "true");
//     check("100 > 99",   (bigint(100) > bigint(99)) ? "true" : "false", "true");
// }


// int main()
// {
//     test_constructors();
//     test_plus();
//     test_increment();
//     test_plus_eq();
//     test_shift();
//     test_compare();

//     std::cout << "\n----------------------------------------" << std::endl;
//     std::cout << "Passed: " << g_pass << "   Failed: " << g_fail << std::endl;
//     return g_fail == 0 ? 0 : 1;
// }


#include "bigint.hpp"
#include <iostream>

int main()
{
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);
    bigint r(0);

    // std::cout << "a = " << a << std::endl;
    // std::cout << "b = " << b << std::endl;
    // std::cout << "c = " << c << std::endl;
    // std::cout << "d = " << d << std::endl;
    // std::cout << "e = " << e << std::endl;

    // std::cout << "a + b = " << a + b << std::endl;
    // std::cout << "(c += a) = " << (c += a) << std::endl;

    // std::cout << "b = " << b << std::endl;
    // std::cout << "++b = " << ++b << std::endl;
    // std::cout << "b++ = " << b++ << std::endl;

    // std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    // std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    // std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;

    // std::cout << "a =" << a << std::endl;
    // std::cout << "d =" << d << std::endl;

    // std::cout << "(d < a) = " << (d < a) << std::endl;
    // std::cout << "(d <= a) = " << (d <= a) << std::endl;
    // std::cout << "(d > a) = " << (d > a) << std::endl;
    // std::cout << "(d >= a) = " << (d >= a) << std::endl;
    // std::cout << "(d == a) = " << (d == a) << std::endl;
    // std::cout << "(d != a) = " << (d != a) << std::endl;
    (r <<= 3);
    std::cout << r << "\n";
}