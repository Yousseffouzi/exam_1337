#include "BigInt.hpp"
#include <sstream>
#include <algorithm>

BigInt::BigInt() : digits("0") {}

BigInt::BigInt(unsigned int nbr)
{
    if(nbr == 0)
    {
        digits = "0";
        return ;
    }
    else
    {
        std::ostringstream oss;
        oss << nbr;
        digits = oss.str();
        std::reverse(digits.begin(), digits.end());
    }
}

BigInt::BigInt(const std::string& nbr)
{
    if(!checkDigits(nbr))
        digits = "0";
    else
    {
        digits = nbr;
        std::reverse(digits.begin(), digits.end());
        removeZeros();
    }
}

bool BigInt::checkDigits(const std::string& s) const
{
    if(s.empty())
        return false;
    
    for (int i = 0; i < (int)s.size(); i++)
    {
        if(!isdigit(s[i]))
            return false;
    }
    return true;
}

bool BigInt::isZero() const
{
    return digits == "0";
}

void BigInt::removeZeros()
{
    if(digits.empty())
    {
        digits = "0";
        return ;
    }

    int i = digits.size() - 1;
    while(i > 1 && digits[i] == '0')
        i--;
    digits = digits.substr(0, i+1);
}

std::string BigInt::addStrs(const std::string& a, const std::string& b) const
{
    std::string res;
    int carry = 0;
    int len = std::max(a.size(), b.size());

    for (int i = 0; i < len || carry; i++)
    {
        int digitA = i < (int) a.size() ? a[i] - '0' : 0;
        int digitB = i < (int) b.size() ? b[i] - '0' : 0;
        int sum = digitA + digitB + carry;

        res.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    return res;
}

BigInt BigInt::operator+(const BigInt& other) const
{
    BigInt res = *this;
    res.digits = addStrs(digits, other.digits);
    res.removeZeros();
    return res;
}

BigInt& BigInt::operator+=(const BigInt& other)
{
    digits = addStrs(digits, other.digits);
    removeZeros();
    return *this;
}

bool BigInt::operator==(const BigInt& other) const
{
    BigInt a = *this, b = other;

    a.removeZeros();
    b.removeZeros();
    return a.digits == b.digits;
}

bool BigInt::operator!=(const BigInt& other) const
{
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const
{
    BigInt a = *this, b = other;

    a.removeZeros();
    b.removeZeros();

    if(a.digits.size() != b.digits.size())
        return a.digits.size() < b.digits.size();

    for (int i = a.digits.size() - 1; i >= 0; i--)
    {
        if(a.digits[i] != b.digits[i])
            return a.digits[i] < b.digits[i];
    }
    return false;
}

bool BigInt::operator>(const BigInt& other) const
{
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const
{
    return !(*this > other);
}

bool BigInt::operator>=(const BigInt& other) const
{
    return !(*this < other);
}

BigInt BigInt::operator<<(unsigned int shift) const
{
    if(isZero() || shift == 0)
        return *this;
    BigInt res = *this;
    res.digits.insert(res.digits.begin(), shift, '0');
    res.removeZeros();
    return res;
}

BigInt BigInt::operator>>(unsigned int shift) const
{
    if(shift == 0)
        return *this;

    BigInt res = *this;
    if(res.digits.size() <= shift)
        res.digits = "0";
    else
        res.digits.erase(res.digits.begin(), res.digits.begin() + shift);
    res.removeZeros();
    return res;
}

BigInt& BigInt::operator<<=(unsigned int shift)
{
    *this = *this << shift;
    return *this;
}

BigInt& BigInt::operator>>=(unsigned int shift)
{
    *this = *this >> shift;
    return *this;
}

BigInt& BigInt::operator<<=(const BigInt& shift)
{
    std::string str = shift.getDigits();
    std::reverse(str.begin(), str.end());

    if(!checkDigits(str))
        return *this;

    unsigned int s = 0;
    for (int i = 0; i < (int) str.size(); i++)
    {
        s = s * 10 + str[i] - '0';
    }
    *this = *this << s;
    return *this;
}

BigInt& BigInt::operator>>=(const BigInt& shift)
{
    std::string str = shift.getDigits();
    std::reverse(str.begin(), str.end());

    if(!checkDigits(str))
        return *this;
    
    unsigned int s = 0;
    for (int i = 0; i < (int) str.size(); i++)
    {
        s = s * 10 + (str[i] - '0');
    }
    *this = *this >> s;
    return *this;
}

BigInt& BigInt::operator++()
{
    *this += BigInt(1);
    return *this;
}

BigInt BigInt::operator++(int)
{
    BigInt res = *this;
    *this += BigInt(1);
    return res;
}

std::string BigInt::getDigits() const
{
    return digits;
}

std::ostream& operator<<(std::ostream& out, const BigInt& nbr)
{
    std::string str(nbr.getDigits());
    std::reverse(str.begin(), str.end());
    out << str;
    return out;
}