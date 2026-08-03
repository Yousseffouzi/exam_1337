#pragma once
#include <iostream>

class bigint
{
    std::string value;
    int i;
    bigint _add(const bigint& other) const;
    bool _isGreaterThan(const bigint& other) const;
public:
    bigint();
    bigint(int value);
    bigint(const std::string& value);
    bigint(const bigint& other);

    bigint operator+(const bigint& other);
    bigint operator+(const bigint& other) const;
    bigint operator+(int value);

    bigint& operator++();
    bigint operator++(int);

    bigint& operator+=(const bigint& other);

    bigint operator>>(const int shift);
    bigint operator<<(const int shift);
    bigint& operator<<=(const int shift);
    bigint& operator>>=(const int shift);

    bool operator>(const bigint& other);
    bool operator>=(const bigint& other);
    bool operator<(const bigint& other);
    bool operator<=(const bigint& other);
    bool operator==(const bigint& other);
    bool operator!=(const bigint& other);
    
    std::string toString() const;
};
std::ostream& operator<<(std::ostream& os, const bigint& value);