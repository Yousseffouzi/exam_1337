#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
    private:
        int _x;
        int _y;

    public:
        // Constructors
        vect2(int x = 0, int y = 0);
        vect2(const vect2 &other);
        vect2 &operator=(const vect2 &other);

        // Access operators
        int &operator[](int index);
        const int &operator[](int index) const;

        // Arithmetic operators
        vect2 operator+(const vect2 &other) const;
        vect2 operator-(const vect2 &other) const;
        vect2 operator*(int carry) const;
        vect2 operator-() const;
        vect2 operator+() const;

        // Compound assignment operators
        vect2 &operator+=(const vect2 &other);
        vect2 &operator-=(const vect2 &other);
        vect2 &operator*=(int carry);

        // Increment / Decrement
        vect2 &operator++();   // Prefix ++
        vect2 operator++(int); // Postfix ++
        vect2 &operator--();   // Prefix --
        vect2 operator--(int); // Postfix --

        // Comparison
        bool operator==(const vect2 &other) const;
        bool operator!=(const vect2 &other) const;

        // Getters
        int getX() const { return _x; }
        int getY() const { return _y; }
};

// Scalar multiplication (commutative)
vect2 operator*(int carry, const vect2 &v);

// Stream output
std::ostream &operator<<(std::ostream &s, const vect2 &v);

#endif
