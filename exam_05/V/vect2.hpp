#pragma once
#include <iostream>

class vect2
{       
    int x, y;
public:
    vect2();
    vect2(int x, int y);
    ~vect2();
    vect2(const vect2 &other);
    vect2 &operator=(const vect2 &other);

    int &operator[](int index);
    const int &operator[](int index) const;

    vect2 &operator++();
    vect2 operator++(int);
    vect2 operator--(int);
    vect2 &operator--();

    vect2 operator+(const vect2 &other) const;
    vect2 operator-(const vect2 &other) const;
    vect2 operator*(int m) const;

    vect2 &operator+=(const vect2 &other);
    vect2 &operator-=(const vect2 &other);
    vect2 &operator*=(int m);

    vect2 operator-() const;

    bool operator==(const vect2 &other) const;
    bool operator!=(const vect2 &other) const;
};
std::ostream &operator<<(std::ostream &os, const vect2 &v);
vect2 operator*(int m, const vect2 &v);

