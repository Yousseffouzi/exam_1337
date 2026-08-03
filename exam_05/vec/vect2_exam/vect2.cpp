#include "vect2.hpp"

vect2::vect2(int x, int y) : _x(x), _y(y)
{
}

vect2::vect2(const vect2 &other)
{
    _x = other._x;
    _y = other._y;
}

vect2 &vect2::operator=(const vect2 &other)
{
    if (this != &other)
    {
        _x = other._x;
        _y = other._y;
    }
    return (*this);
}

int &vect2::operator[](int index)
{
    if (index == 0)
        return (_x);
    else
        return (_y);
}

const int &vect2::operator[](int index) const
{
    if (index == 0)
        return (_x);
    else
        return (_y);
}

vect2 vect2::operator+(const vect2 &other) const
{
    return (vect2(_x + other._x, _y + other._y));
}

vect2 vect2::operator-(const vect2 &other) const
{
    return (vect2(_x - other._x, _y - other._y));
}

vect2 vect2::operator*(int carry) const
{
    return (vect2(_x * carry, _y * carry));
}

vect2 vect2::operator-() const
{
    return (vect2(-_x, -_y));
}

vect2 vect2::operator+() const
{
    return (*this);
}

vect2 &vect2::operator+=(const vect2 &other)
{
    _x += other._x;
    _y += other._y;
    return (*this);
}

vect2 &vect2::operator-=(const vect2 &other)
{
    _x -= other._x;
    _y -= other._y;
    return (*this);
}

vect2 &vect2::operator*=(int carry)
{
    _x *= carry;
    _y *= carry;
    return (*this);
}

vect2 &vect2::operator++()
{
    ++_x;
    ++_y;
    return (*this);
}

vect2 vect2::operator++(int)
{
    vect2 tmp(*this);
    ++(*this);
    return (tmp);
}

vect2 &vect2::operator--()
{
    --_x;
    --_y;
    return (*this);
}

vect2 vect2::operator--(int)
{
    vect2 tmp(*this);
    --(*this);
    return (tmp);
}

bool vect2::operator==(const vect2 &other) const
{
    return (_x == other._x && _y == other._y);
}

bool vect2::operator!=(const vect2 &other) const
{
    return (!(*this == other));
}

vect2 operator*(int carry, const vect2 &v)
{
    return (vect2(v.getX() * carry, v.getY() * carry));
}

std::ostream &operator<<(std::ostream &s, const vect2 &v)
{
    s << "{" << v.getX() << ", " << v.getY() << "}";
    return s;
}
