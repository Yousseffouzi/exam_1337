#include "bigint.hpp"
#include <sstream>
#include <algorithm>

bigint::bigint()
{
    value = "0";
}

bigint::bigint(const std::string& value)
{
    this->value = value;
}

bigint::bigint(int value)
{
    std::stringstream ss;
    ss << value;
    this->value = ss.str();
    i = value;
}

bigint::bigint(const bigint& other)
{
    this->value = other.value;
}

bigint bigint::operator+(const bigint& other)
{
    return _add(other);
}

bigint bigint::operator+(const bigint& other) const
{
    return _add(other);
}

bigint bigint::_add(const bigint& other) const
{
    std::stringstream ss;
    int sum = 0;
    for(size_t i = 0; i < value.size() || i < other.value.size(); ++i)
    {
        int digit1 = (i < value.size()) ? value[value.size() - 1 - i] - '0' : 0;
        int digit2 = (i < other.value.size()) ? other.value[other.value.size() - 1 - i] - '0' : 0;
        sum += digit1 + digit2;
        ss << sum % 10;
        sum /= 10;
    }
    if (sum > 0)
        ss << sum;
    std::string result = ss.str();
    std::reverse(result.begin(), result.end());
    return bigint(result);
}

bigint bigint::operator+(int value)
{
    return *this + bigint(value);
}

bigint& bigint::operator++()
{
    *this = *this + 1;
    return *this;
}

bigint bigint::operator++(int)
{
    bigint temp = *this;
    *this = *this + 1;
    return temp;
}

bigint& bigint::operator+=(const bigint& other)
{
    *this = *this + other;
    return *this;
}

bigint bigint::operator>>(const int shift)
{
    std::string newValue = value;
    return bigint(newValue.erase(newValue.size() - shift));
}

bigint bigint::operator<<(const int shift)
{
    return bigint(value + std::string(shift, '0'));
}

bigint& bigint::operator<<=(const int shift)
{
    *this = *this << shift;
    return *this;
}

bigint& bigint::operator>>=(const int shift)
{
    *this = *this >> shift;
    return *this;
}

bool bigint::_isGreaterThan(const bigint& other) const
{
    if (value.size() != other.value.size())
        return value.size() > other.value.size();
    for (size_t i = 0; i < value.size(); ++i)
    {
        if (value[i] != other.value[i])
            return value[i] > other.value[i];
    }
    return false;
}

bool bigint::operator>(const bigint& other)
{
    return _isGreaterThan(other);
}


bool bigint::operator>=(const bigint& other)
{
    return _isGreaterThan(other) || this->value == other.value;
}

bool bigint::operator<(const bigint& other)
{
    return !(*this >= other);
}

bool bigint::operator<=(const bigint& other)
{
    return !(*this > other);
}

bool bigint::operator==(const bigint& other)
{
    return this->value == other.value;
}

bool bigint::operator!=(const bigint& other)
{
    return !(*this == other);
}

std::string bigint::toString() const
{
    return value;
}

std::ostream& operator<<(std::ostream& os, const bigint& value)
{
    os << value.toString();
    return os;
}
