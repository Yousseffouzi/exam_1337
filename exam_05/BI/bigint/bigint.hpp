#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

class bigint
{
private:
	std::string _value;

public:
	bigint();
	bigint(unsigned long long n);//number
	bigint(const std::string &str);//string
	bigint &operator=(const bigint &src);
	bigint(const bigint &src);
	~bigint();

	std::string getStr() const;


	
	bigint operator+(const bigint &other) const;
	bigint &operator+=(const bigint &other);

	bigint &operator++();
	bigint operator++(int);

	bigint operator<<(unsigned int n) const;
	bigint operator>>(unsigned int n) const;
	bigint &operator<<=(unsigned int n);
	bigint &operator>>=(unsigned int n);

	bigint operator<<(const bigint &other) const;
	bigint operator>>(const bigint &other) const;
	bigint &operator<<=(const bigint &other);
	bigint &operator>>=(const bigint &other);

	bool operator==(const bigint &other) const;
	bool operator!=(const bigint &other) const;
	bool operator<(const bigint &other) const;
	bool operator>(const bigint &other) const;
	bool operator<=(const bigint &other) const;
	bool operator>=(const bigint &other) const;

	std::string toString() const;
};

std::ostream &operator<<(std::ostream &out, const bigint &obj);

#endif
