#include "BigInt.hpp"

BigInt::BigInt() : value("0")
{}

BigInt::BigInt(const BigInt &other) : value(other.value)
{}

BigInt &BigInt::operator=(const BigInt &other)
{
    if (this != &other)
        value = other.value;
    return *this;
}

BigInt::BigInt(unsigned long n)
{
    std::stringstream ss;
    ss << n;
    value = ss.str();
}

BigInt::BigInt(const std::string &str)
{
    for (size_t i = 0; i < str.size(); i++){
        if (!isdigit(str[i])){
            value = "0";
            return ;
        }
    }
    
    size_t z = 0;
    while (z < str.size() && str[z] == '0')
        z++;
    if( z == str.size())
        value = "0";
    else
        value = str.substr(z);
}

BigInt BigInt::operator++(int)
{
    BigInt tmp = *this;
    *this = *this + BigInt(1);
    return tmp;

}

BigInt &BigInt::operator++()
{
    *this = *this + BigInt(1);
    return *this;
}
// 123 >> 1 = 12
BigInt BigInt::operator>>(unsigned int n) const
{
    BigInt tmp = *this;
    int len = tmp.value.length();

    if (n >= len)
        tmp.value = "0";
    else
        tmp.value = tmp.value.erase(tmp.value.length() - n, n);
    return tmp;
}

BigInt BigInt::operator<<(unsigned int n) const
{
    BigInt tmp = *this;

    if (tmp.value != "0")
        tmp.value.insert(tmp.value.end() ,n ,'0');
    return tmp;
}

BigInt &BigInt::operator>>=(unsigned int n)
{
    *this = *this >> n;
    return *this;
}

BigInt &BigInt::operator<<=(unsigned int n)
{
    *this = *this << n;
    return *this;
}

unsigned int stringToInt(const std::string &str)
{
    std::stringstream ss(str);//this 
    unsigned int res = 0;
    ss >> res;
    return res;
}

BigInt BigInt::operator>>(const BigInt &other) const
{
    BigInt tmp = *this;
    tmp = *this >> stringToInt(other.value);//this
    return tmp;
}

BigInt BigInt::operator<<(const BigInt &other) const
{
    BigInt tmp = *this;
    tmp = *this << stringToInt(other.value);
    return tmp;
}

BigInt &BigInt::operator>>=(const BigInt &other)
{
    *this = *this >> other;
    return *this;
}

BigInt &BigInt::operator<<=(const BigInt &other)
{
    *this = *this << other;
    return *this;
}

BigInt BigInt::operator+(const BigInt &other) const
{
    std::string res = "";
    int sum = 0;
    int carry = 0;
    
    int i = value.length() -1;
    int j = other.value.length() -1;

    while (i >= 0 || j >= 0 || carry)
    {
        int nbr1,nbr2;
        if (i >= 0)
            nbr1 = value[i] - '0';
        else
            nbr1 = 0;
        if (j >= 0)
            nbr2 = other.value[j] - '0';
        else
            nbr2 = 0;
        sum = nbr1 + nbr2 + carry;
        carry = sum / 10;
        sum %= 10;
        res = static_cast<char>(sum + '0') + res;
        i--; j--;
    }
    return BigInt(res);
}

BigInt &BigInt::operator+=(const BigInt &other)
{
    *this = *this + other;
    return *this;
}

std::string BigInt::getValue() const
{
    return value;
}

std::ostream &operator<<(std::ostream &os, const BigInt &value)
{
    os << value.getValue();
    return os;
}


bool BigInt::operator==(const BigInt &other) const
{
    return (value == other.value);
}

bool BigInt::operator!=(const BigInt &other) const
{
    return !(*this == other);
}

bool BigInt::operator>(const BigInt &other) const
{
    if (value.length() != other.value.length())
        return (value.length() > other.value.length());
    return value > other.value;
}

bool BigInt::operator<(const BigInt &other) const
{
    return other > *this;
}

bool BigInt::operator>=(const BigInt &other) const
{
    return !(*this < other);
}

bool BigInt::operator<=(const BigInt &other) const
{
    return !(*this > other);
}

