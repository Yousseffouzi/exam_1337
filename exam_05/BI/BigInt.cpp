#include "BigInt.hpp"

bigint::bigint(): str("0")
{
}

bigint::bigint(const bigint &other) : str(other.str)
{
}

bigint::bigint(unsigned int num)
{
    std::stringstream ss;
    ss << num;
    str = ss.str(); 
}

bigint &bigint::operator=(const bigint &other)
{
    if(this != &other)
        str = other.str;
    return *this;
}

bigint::~bigint()
{
}

bigint bigint::operator+(const bigint &other) const
{
    int i = str.size() -1;
    int j = other.str.size() -1;
    int carry = 0;
    int sum = 0;
    std::string result;
    while (i >= 0 || j >= 0 || carry)
    {
        int nbr1,nbr2;
        if(i >= 0)
            nbr1 = str[i] - '0';
        else
            nbr1 = 0;
        if (j >= 0)
            nbr2 = other.str[j] - '0';
        else
            nbr2 = 0;
        sum = nbr1 + nbr2 + carry;
        carry = sum / 10;
        sum %= 10;
        result = static_cast<char>(sum + '0') + result;
        i--,j--;
    }
    bigint res;
    res.str = result;
    return res;
}

bigint &bigint::operator+=(const bigint &other)
{
    *this = *this + other;
    return *this;
}

bigint &bigint::operator++()
{
    *this = *this + bigint(1);
    return *this;
}

bigint bigint::operator++(int)
{
    bigint tmp = *this;
    ++(*this);
    return tmp;
}



bigint bigint::operator>>(unsigned int shift) const
{
    bigint tmp = *this;
    int len = tmp.str.size();
    if(shift >= len)
        tmp.str = "0";
    else
        tmp.str.erase(len - shift, shift);
    return tmp;
}

bigint bigint::operator<<(unsigned int shift) const
{
    bigint tmp = *this;
    if(tmp.str == "0")
        return tmp;
    tmp.str.insert(tmp.str.end(), shift, '0');
    return tmp;
}

bigint &bigint::operator>>=(unsigned int shift)
{
    *this = *this >> shift;
    return *this;
}

bigint &bigint::operator<<=(unsigned int shift)
{
    *this = *this << shift;
    return *this;
}
static unsigned int toInt(std::string str)
{
    std::stringstream ss(str);
    unsigned int res;
    ss >> res;
    return res;
}
bigint bigint::operator>>(const bigint &other) const
{
    bigint tmp;
    tmp = tmp >> toInt(other.str);
    return tmp;
}

bigint bigint::operator<<(const bigint &other) const
{
    bigint tmp;
    tmp = tmp << toInt(other.str);
    return tmp;
}

bigint &bigint::operator>>=(const bigint &other)
{
    *this = *this >> other;
    return *this;
}

bigint &bigint::operator<<=(const bigint &other)
{
    *this = *this << other;
    return *this;
}

bool bigint::operator>(const bigint &other) const
{
    if(str.length() != other.str.length())
        return (str.length() > other.str.length());
    return str > other.str;
}

bool bigint::operator<(const bigint &other) const
{
    return !(*this > other);
}

bool bigint::operator>=(const bigint &other) const
{
    return !(other > *this);
}

bool bigint::operator<=(const bigint &other) const
{
    return !(*this > other);
}

bool bigint::operator==(const bigint &other) const
{
    return (str == other.str);
}

bool bigint::operator!=(const bigint &other) const
{
    return !(*this == other);
}

        
std::string bigint::getStr() const
{
    return str;
}

std::ostream &operator<<(std::ostream &os, const bigint &v)
{
    os << v.getStr();
    return os;
}