#ifndef BigInt_HPP
#define BigInt_HPP

#include <iostream>
#include <string>


class BigInt
{
private:
    std::string num;
    void normalize();
public:
    BigInt();
    BigInt(unsigned long n);
    BigInt(const std::string& s);
    BigInt(const BigInt& other);

    BigInt  operator+(const BigInt& other) const;
    BigInt& operator=(const BigInt& other);

    bool    operator==(const BigInt& other) const;
    bool    operator<(const BigInt& other) const;
    bool    operator>=(const BigInt& other) const;
    bool    operator<=(const BigInt& other) const;
    bool    operator!=(const BigInt& other) const;
    bool    operator>(const BigInt& other) const;

    BigInt operator<<(unsigned int n) const;
    BigInt operator>>(unsigned int n) const;
    
    friend std::ostream& operator<<(std::ostream& os, const BigInt& b);
};

#endif