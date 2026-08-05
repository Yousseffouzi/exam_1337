#include "vect2.hpp"

vect2::vect2() : x(0) , y(0)
{}
vect2::vect2(int x, int y) : x(x) , y(y) 
{}
vect2::vect2(const vect2 &other)
{
    if(this != &other){
        x = other.x;
        y = other.y;
    }
}
vect2 &vect2::operator=(const vect2 &other)
{
    x = other.x;
    y = other.y;
}

int &vect2::operator[](int index)
{
    if (index == 0)
        return x;
    else
        return y;
}
const int &vect2::operator[](int index) const
{
    if (index == 0)
        return x;
    else
        return y;
}

vect2 &vect2::operator++()
{
    x++;
    y++;
    return *this;
}
vect2 vect2::operator++(int)
{
    vect2 tmp = *this;
    ++(*this);
    return tmp; 
}
vect2 &vect2::operator--()
{
    x--;
    y--;
    return *this;
}
vect2 vect2::operator--(int)
{
    vect2 tmp = *this;
    --(*this);
    return tmp; 
}

vect2 vect2::operator+(const vect2 &other) const
{
    vect2 tmp = *this;
    tmp.x + other.x;
    tmp.y + other.y;
    return tmp;
}
vect2 vect2::operator-(const vect2 &other) const
{
    vect2 tmp = *this;
    tmp.x - other.x;
    tmp.y - other.y;
    return tmp;
}
vect2 vect2::operator*(int carry) const
{
    vect2 tmp = *this;
    tmp.x * carry;
    tmp.y * carry;
    return tmp;
}

vect2 &vect2::operator+=(const vect2 &other)
{
    x += other.x;
    y += other.y;
    return (*this);
}
vect2 &vect2::operator-=(const vect2 &other)
{
    x -= other.x;
    y -= other.y;
    return (*this);
}
vect2 &vect2::operator*=(int carry)
{
    x *= carry;
    y *= carry;
    return (*this);
}

vect2 vect2::operator-() const
{
    return (vect2(-x, -y));
}

bool vect2::operator==(const vect2 &other) const
{
    return (x == other.x && y == other.y);
}
bool vect2::operator!=(const vect2 &other) const
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const vect2 &v)
{
    os << "{" << v[0] << ", " << v[1] << "}" << std::endl;
    return os;
}
vect2   operator*(int carry, const vect2 &v)
{
    return v * carry;
}
