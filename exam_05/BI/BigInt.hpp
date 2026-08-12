#pragma once

#include <iostream>
#include <sstream>
#include <string>

class bigint
{
    std::string str;
    public:
        bigint();
        bigint(const bigint &other);
        bigint(unsigned int num);
        bigint &operator=(const bigint &other);
        ~bigint();

        bigint operator+(const bigint &other) const;
        bigint &operator+=(const bigint &other);

        bigint operator++(int);
        bigint &operator++();

        bigint operator>>(unsigned int shift) const;
        bigint operator<<(unsigned int shift) const;
        bigint &operator>>=(unsigned int shift);
        bigint &operator<<=(unsigned int shift);

        bigint operator>>(const bigint &other) const;
        bigint operator<<(const bigint &other) const;
        bigint &operator>>=(const bigint &other);
        bigint &operator<<=(const bigint &other);

        bool operator>(const bigint &other) const;
        bool operator<(const bigint &other) const;
        bool operator>=(const bigint &other) const;
        bool operator<=(const bigint &other) const;
        bool operator==(const bigint &other) const;
        bool operator!=(const bigint &other) const;
        
        std::string getStr() const;
};
std::ostream &operator<<(std::ostream &os, const bigint &v);
