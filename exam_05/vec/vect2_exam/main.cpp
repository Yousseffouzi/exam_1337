#include "vect2.hpp"

int main()
{
    vect2 a(2, 3);
    vect2 b(1, 4);
    vect2 c;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;

    std::cout << "\n=== Arithmetic Tests ===\n";
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * 2 = " << (a * 2) << std::endl;
    std::cout << "2 * b = " << (2 * b) << std::endl;
    std::cout << "-a = " << (-a) << std::endl;

    std::cout << "\n=== Compound Assignments ===\n";
    c = a;
    c += b;
    std::cout << "a += b → " << c << std::endl;
    c = a;
    c -= b;
    std::cout << "a -= b → " << c << std::endl;
    c = a;
    c *= 3;
    std::cout << "a *= 3 → " << c << std::endl;

    std::cout << "\n=== Increment / Decrement ===\n";
    vect2 d(5, 5);
    std::cout << "Original d: " << d << std::endl;
    std::cout << "d++ = " << d++ << " (after: " << d << ")" << std::endl;
    std::cout << "++d = " << ++d << std::endl;
    std::cout << "d-- = " << d-- << " (after: " << d << ")" << std::endl;
    std::cout << "--d = " << --d << std::endl;

    std::cout << "\n=== Comparison ===\n";
    std::cout << "a == b ? " << (a == b ? "true" : "false") << std::endl;
    std::cout << "a != b ? " << (a != b ? "true" : "false") << std::endl;

    std::cout << "\n=== Access via [] ===\n";
    std::cout << "a[0] = " << a[0] << ", a[1] = " << a[1] << std::endl;

    return 0;
}
