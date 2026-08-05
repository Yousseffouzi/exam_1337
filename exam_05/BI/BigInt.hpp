#pragma once

#include <iostream>
#include <sstream>

class BigInt
{
    std::string value;
    public:
        BigInt();
        BigInt(const BigInt &other);
        BigInt(const std::string &str);
        BigInt &operator=(const BigInt &other);
        BigInt(unsigned long n);

        BigInt operator++(int);
        BigInt &operator++();

        BigInt operator+(const BigInt &other) const;
        BigInt &operator+=(const BigInt &other);

        BigInt operator>>(unsigned int n) const;
        BigInt operator<<(unsigned int n) const;
        BigInt &operator>>=(unsigned int n);
        BigInt &operator<<=(unsigned int n);

        BigInt operator>>(const BigInt &other) const;
        BigInt operator<<(const BigInt &other) const;
        BigInt &operator>>=(const BigInt &other);
        BigInt &operator<<=(const BigInt &other);

        bool operator==(const BigInt &other) const;
        bool operator!=(const BigInt &other) const;
        bool operator>(const BigInt &other) const;
        bool operator<(const BigInt &other) const;
        bool operator>=(const BigInt &other) const;
        bool operator<=(const BigInt &other) const;

        std::string getValue() const;
};
std::ostream &operator<<(std::ostream &os, const BigInt &value);
