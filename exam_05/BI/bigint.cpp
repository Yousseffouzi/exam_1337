#pragma once
#include <iostream>
#include <sstream>
#include <algorithm>

class bigint
{
    private:
        std::string value;
        int i;
        bigint add(const bigint &other) const;
        bool is_greaterThen(const bigint &other) const;
    public:
        bigint();
        bigint(const bigint &other);
        bigint(int value);
        bigint(const std::string &value);
        
};