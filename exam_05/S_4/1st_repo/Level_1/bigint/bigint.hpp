#ifndef BigInt_HPP
#define BigInt_HPP
#include <iostream>
#include <string>
#include <algorithm>

class BigInt {
	std::string value;
	std::string add(const std::string& num1, const std::string& num2) const {
		std::string result; int carry=0,i=num1.size()-1,j=num2.size()-1;
		while(i>=0||j>=0||carry){
			int sum=carry+(i>=0?num1[i--]-'0':0)+(j>=0?num2[j--]-'0':0);
			result+=char('0'+sum%10); carry=sum/10;
		}
		return std::string(result.rbegin(),result.rend());
	}
public:
	BigInt():value("0"){}
	BigInt(const BigInt& other):value(other.value){}
	BigInt& operator=(const BigInt& other){if(this!=&other)value=other.value;return *this;}
	~BigInt(){}
	BigInt(unsigned long num):value(num?"":"0"){while(num)value=char('0'+num%10)+value,num/=10;}
	BigInt(const std::string& str):value(str.empty()?"0":str){}
	BigInt operator+(const BigInt& other)const{return BigInt(add(value,other.value));}
	BigInt& operator+=(const BigInt& other){value=add(value,other.value);return *this;}
	bool operator<(const BigInt& other)const{return value.size()!=other.value.size()?value.size()<other.value.size():value<other.value;}
	bool operator>(const BigInt& other)const{return other<*this;}
	bool operator<=(const BigInt& other)const{return !(other<*this);}
	bool operator>=(const BigInt& other)const{return !(*this<other);}
	bool operator==(const BigInt& other)const{return value==other.value;}
	bool operator!=(const BigInt& other)const{return value!=other.value;}
	BigInt operator<<(size_t shift)const{return BigInt(value+std::string(shift,'0'));}
	BigInt& operator<<=(size_t shift){value+=std::string(shift,'0');return *this;}
	BigInt operator>>(size_t shift)const{return shift>=value.size()?BigInt():BigInt(value.substr(0,value.size()-shift));}
	BigInt& operator>>=(size_t shift){value=shift>=value.size()?"0":value.substr(0,value.size()-shift);return *this;}
	BigInt& operator++(){return *this+=BigInt(1);}
	BigInt operator++(int){BigInt temp(*this);++(*this);return temp;}
	friend std::ostream& operator<<(std::ostream& os,const BigInt& x){return os<<x.value;}
};
#endif
