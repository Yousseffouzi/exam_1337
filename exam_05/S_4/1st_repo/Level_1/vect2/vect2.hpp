#ifndef VECT2_HPP
#define VECT2_HPP
#include <iostream>

class vect2 {
	int x, y;
public:
	vect2():x(0),y(0){}
	vect2(int x,int y):x(x),y(y){}
	vect2(const vect2& other):x(other.x),y(other.y){}
	~vect2(){}
	vect2& operator=(const vect2& other){if(this!=&other){x=other.x;y=other.y;}return *this;}
	vect2& operator+=(const vect2& other){x+=other.x;y+=other.y;return *this;}
	vect2& operator-=(const vect2& other){x-=other.x;y-=other.y;return *this;}
	vect2& operator++(){++x;++y;return *this;}
	vect2& operator--(){--x;--y;return *this;}
	int& operator[](int i){return i?y:x;}
	const int& operator[](int i)const{return i?y:x;}
	vect2 operator+(const vect2& other)const{return vect2(x+other.x,y+other.y);}
	vect2 operator-(const vect2& other)const{return vect2(x-other.x,y-other.y);}
	bool operator==(const vect2& other)const{return x==other.x&&y==other.y;}
	bool operator!=(const vect2& other)const{return !(*this==other);}
	vect2 operator*(int other)const{return vect2(x*other,y*other);}
	vect2 operator++(int){vect2 other(*this);++*this;return other;}
	vect2 operator--(int){vect2 other(*this);--*this;return other;}
	friend vect2 operator*(int scalar,const vect2& other){return other*scalar;}
	friend std::ostream& operator<<(std::ostream& os,const vect2& other){return os<<"{"<<other.x<<", "<<other.y<<"}";}
};
#endif
