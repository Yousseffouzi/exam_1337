#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include <string>
#include <algorithm>

class bigint {
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
	bigint():value("0"){}
	bigint(const bigint& other):value(other.value){}
	bigint& operator=(const bigint& other){if(this!=&other)value=other.value;return *this;}
	~bigint(){}
	bigint(unsigned long num):value(num?"":"0"){while(num)value=char('0'+num%10)+value,num/=10;}
	bigint(const std::string& str):value(str.empty()?"0":str){}
	bigint operator+(const bigint& other)const{return bigint(add(value,other.value));}
	bigint& operator+=(const bigint& other){value=add(value,other.value);return *this;}
	bool operator<(const bigint& other)const{return value.size()!=other.value.size()?value.size()<other.value.size():value<other.value;}
	bool operator>(const bigint& other)const{return other<*this;}
	bool operator<=(const bigint& other)const{return !(other<*this);}
	bool operator>=(const bigint& other)const{return !(*this<other);}
	bool operator==(const bigint& other)const{return value==other.value;}
	bool operator!=(const bigint& other)const{return value!=other.value;}
	bigint operator<<(size_t shift)const{return bigint(value+std::string(shift,'0'));}
	bigint& operator<<=(size_t shift){value+=std::string(shift,'0');return *this;}
	bigint operator>>(size_t shift)const{return shift>=value.size()?bigint():bigint(value.substr(0,value.size()-shift));}
	bigint& operator>>=(size_t shift){value=shift>=value.size()?"0":value.substr(0,value.size()-shift);return *this;}
	bigint& operator++(){return *this+=bigint(1);}
	bigint operator++(int){bigint temp(*this);++(*this);return temp;}
	friend std::ostream& operator<<(std::ostream& os,const bigint& x){return os<<x.value;}
};
#endif
