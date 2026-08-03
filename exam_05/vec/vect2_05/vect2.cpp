#include "vect2.hpp"

vect2::vect2(): x(0), y(0)
{}

vect2::vect2(int x, int y): x(x), y(y)
{}

vect2::vect2(const vect2& other)
{
    x = other.x;
    y = other.y;
}

vect2& vect2::operator=(const vect2& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
    os << "{" << v[0] << ", " << v[1] << "}";
    return os;
}

int vect2::operator[](int index) const
{
    if (index == 0)
        return x;
    else if (index == 1)
        return y;
    else
        throw std::out_of_range("Index out of range");
}

int &vect2::operator[](int index)
{
    if (index == 0)
        return x;
    else if (index == 1)
        return y;
    else
        throw std::out_of_range("Index out of range");
}

vect2 vect2::operator++(int)
{
    vect2 temp = *this;
    x++;
    y++;
    return temp;
}

vect2& vect2::operator++()
{
    x++;
    y++;
    return *this;
}

vect2 vect2::operator--(int)
{
    vect2 temp = *this;
    x--;
    y--;
    return temp;
}

vect2& vect2::operator--()
{
    x--;
    y--;
    return *this;
}

vect2& vect2::operator+=(const vect2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

vect2& vect2::operator*=(const vect2& other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

vect2& vect2::operator-=(const vect2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

vect2 vect2::operator*(const vect2& other)
{
    vect2 temp = *this;
    temp.x *= other.x;
    temp.y *= other.y;
    return temp;
}

vect2 vect2::operator+(const vect2& other) const
{
    vect2 temp = *this;
    temp.x += other.x;
    temp.y += other.y;
    return temp;
}

vect2 vect2::operator-(const vect2& other) const
{
    vect2 temp = *this;
    temp.x -= other.x;
    temp.y -= other.y;
    return temp;
}

vect2 vect2::operator-() const
{
    vect2 temp = *this;
    temp.x = -x;
    temp.y = -y;
    return temp;
}

vect2 vect2::operator*(int scalar) const
{
    vect2 temp = *this;
    temp.x *= scalar;
    temp.y *= scalar;
    return temp;
}

vect2& vect2::operator*=(int scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

vect2 operator*(int scalar, const vect2& v)
{
    return v * scalar;
}

bool vect2::operator==(const vect2& other) const
{
    return x == other.x && y == other.y;
}

bool vect2::operator!=(const vect2& other) const
{
    return !(*this == other);
}
