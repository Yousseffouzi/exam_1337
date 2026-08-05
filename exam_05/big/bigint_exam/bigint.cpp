#include "bigint.hpp"

bigint::bigint()
{
    _value = "0";
}

bigint::bigint(unsigned long long n)
{
	std::stringstream ss;
	ss << n;
	_value = ss.str();
}

bigint::bigint(const std::string &str)
{
    for (size_t i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])) {
            _value = "0";
            return;
        }
    }

    size_t zero = 0;
    while (zero < str.size() && str[zero] == '0')
        zero++;

    if (zero == str.size())
        _value = "0";
    else
        _value = str.substr(zero);
}

bigint::bigint(const bigint &src) : _value(src._value)
{
}

bigint::~bigint()
{
}

std::string bigint::getStr() const
{
    return (_value);
}

bigint &bigint::operator=(const bigint &src)
{
    if (this != &src)
        _value = src._value;

    return (*this);
}

bigint bigint::operator+(const bigint &other) const
{
    std::string result = "";
    int carry = 0;
    int sum;

    int i = _value.size() - 1;
    int j = other._value.size() - 1;

    // "12345" + "123456"
    while (i >= 0 || j >= 0 || carry)
    {
        int nbr1, nbr2;

        if (i >= 0)
            nbr1 = _value[i] - '0';
        else
            nbr1 = 0;
        if (j >= 0)
            nbr2 = other._value[j] - '0';
        else
            nbr2 = 0;
        
        sum = nbr1 + nbr2 + carry;
        carry = sum / 10;
        sum = sum % 10;

        result = static_cast<char>(sum + '0') + result;
        
        i--; j--;
    }

    return bigint(result);
}

bigint &bigint::operator+=(const bigint &other)
{
    *this = *this + other;
    return (*this);
}

bigint &bigint::operator++()
{
    *this = *this + bigint(1);
    return (*this);
}

bigint bigint::operator++(int)
{
    bigint tmp = *this;
    *this = *this + bigint(1);
    return (tmp);
}

bigint bigint::operator<<(unsigned int n) const
{
    bigint temp = *this;
    if (temp._value == "0")
        return (temp);
    temp._value.insert(temp._value.end(), n, '0');
    return (temp);
}

bigint bigint::operator>>(unsigned int n) const
{
    bigint tmp = *this;
    size_t len = tmp._value.length();
    if (n >= len)
        tmp._value = "0";
    else
        tmp._value.erase(tmp._value.length() - n, n);
    return (tmp);
}

bigint &bigint::operator<<=(unsigned int n)
{
    *this = *this << n;
    return (*this);
}

bigint &bigint::operator>>=(unsigned int n)
{
    *this = *this >> n;
    return (*this);
}

unsigned int stringToUINT(std::string str)
{
    std::stringstream ss(str);
    unsigned int res;
    ss >> res;
    return (res);
}

bigint bigint::operator<<(const bigint &other) const
{
    bigint tmp;
    tmp = *this << stringToUINT(other._value);
    return (tmp);
}

bigint bigint::operator>>(const bigint &other) const
{
    bigint tmp;
    tmp = (*this) >> stringToUINT(other._value);
    return (tmp);
}

bigint &bigint::operator<<=(const bigint &other)
{
    *this = *this << stringToUINT(other._value);
    return (*this);
}

bigint &bigint::operator>>=(const bigint &other)
{
    *this = *this >> stringToUINT(other._value);
    return (*this);
}

bool bigint::operator==(const bigint &other) const
{
    return (_value == other._value);
}

bool bigint::operator!=(const bigint &other) const
{
    return (!(*this == other));
}

bool bigint::operator<(const bigint &other) const
{
    if (_value.length() != other._value.length())
        return (_value.length() < other._value.length());

    return (_value < other._value);
}

bool bigint::operator>(const bigint &other) const
{
    return (other < *this);
}

bool bigint::operator<=(const bigint &other) const
{
    return (!(*this > other));
}

bool bigint::operator>=(const bigint &other) const
{
    return (!(*this < other));
}

std::ostream &operator<<(std::ostream &out, const bigint &obj)
{
    out << obj.getStr();
    return (out);
}

std::string bigint::toString() const
{
    return _value;
}
