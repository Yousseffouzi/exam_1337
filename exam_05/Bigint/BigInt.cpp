#include "BigInt.hpp"

BigInt::BigInt()
{
    num = "0";
}

BigInt::BigInt(unsigned long n)
{
    num = std::to_string(n);
}

BigInt& BigInt::operator=(const BigInt& other)
{
    if (this != &other)
        num = other.num;
    return *this;

}

BigInt::BigInt(const std::string& s)
{
    num = s;
    normalize();
}

BigInt::BigInt(const BigInt& other)
{
    num = other.num;
}

void BigInt::normalize()
{
    size_t pos = num.find_first_not_of('0');
    if (pos == std::string::npos)
    {
        num = "0";
        return ;
    }
    num = num.substr(pos);
}

BigInt BigInt::operator+(const BigInt& other) const
{
    std::string result;
    int i = num.size() - 1;
    int j = other.num.size() - 1;
    int carry = 0;
    int a, b;

    while (i >= 0 || j >= 0 || carry > 0)
    {
        if (i >= 0)
            a = num[i] - '0';
        else
            a = 0;
        if (j >= 0)
            b = other.num[j] - '0';
        else
            b = 0;
        int sum = a + b + carry;
        carry = sum / 10;
        result = (char)((sum % 10) + '0') + result;
        i--;
        j--;
    }
    return BigInt(result);
}

bool BigInt::operator==(const BigInt& other) const
{
    return (num == other.num);
}

bool BigInt::operator>(const BigInt& other) const
{
    if (this != &other)
        return num.size() > other.num.size();
    return num > other.num;
}

bool BigInt::operator<(const BigInt& other) const
{
    return !(num > other.num);
}

bool BigInt::operator>=(const BigInt& other) const
{
    return (num >= other.num);
}

bool BigInt::operator<=(const BigInt& other) const
{
    return (num <= other.num);
}

bool BigInt::operator!=(const BigInt& other) const
{
    return (num != other.num);
}