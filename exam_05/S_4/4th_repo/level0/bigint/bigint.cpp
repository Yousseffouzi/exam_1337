/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatkeski <fatkeski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:27:29 by fatkeski          #+#    #+#             */
/*   Updated: 2025/07/26 18:15:45 by fatkeski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"

BigInt::BigInt()
{
	this->str = "0";
}

BigInt::BigInt(unsigned int num)
{
	std::stringstream ss;
	ss << num;
	this->str = ss.str();
	// std::cout << "str: " << str << std::endl;
}

BigInt::BigInt(const BigInt& source)
{
	(*this) = source;
}

BigInt& BigInt::operator=(const BigInt& source)
{
	if(this == &source)
		return(*this);
	this->str = source.str;
	return(*this);
}

std::string BigInt::getStr() const
{
	return(this->str);
}

std::string reverse(const std::string& str)
{
	std::string revStr;
	for(size_t i = str.length(); i > 0; i--)
	{
		revStr.push_back(str[i - 1]);
	}
	return(revStr);
}

std::string addition(const BigInt& obj1, const BigInt& obj2)
{
	std::string str1 = reverse(obj1.getStr());
	std::string str2 = reverse(obj2.getStr());
	std::string result;
	size_t len1 = str1.length();
	size_t len2 = str2.length();

	if(len1 > len2)
	{
		int diff = len1 - len2;
		while(diff > 0)
		{
			str2.push_back('0');
			diff--;
		}
	}
	else if(len2 > len1)
	{
		int diff = len2 - len1;
		while(diff > 0)
		{
			str1.push_back('0');
			diff--;
		}
	}

	int carry = 0;
	int digit1;
	int digit2;
	size_t len = str1.length();
	for(size_t i = 0; i < len; i++)
	{
		digit1 = str1[i] - '0';
		// std::cout <<  "digit1:" << digit1 << std::endl;
		digit2 = str2[i] - '0';
		// std::cout << "digit2:" << digit2 << std::endl;
		int res = digit1 + digit2 + carry;
		// std::cout << res << std::endl;
		if(res > 9)
		{
			carry = res / 10;
			result.push_back((res % 10) + '0');
		}
		else
			result.push_back(res + '0');
	}
	if(carry != 0)
		result.push_back(carry + '0');
	return(reverse(result));
}

BigInt BigInt::operator+(const BigInt& other)const
{
	BigInt temp(other);
	temp.str.clear();
	std::string result = addition(*this, other);
	temp.str = result;
	//std::cout << "r: " << result << std::endl;

	return(temp);
}

BigInt& BigInt::operator+=(const BigInt& other)
{
	(*this) = (*this) + other;
	return(*this);
}

BigInt& BigInt::operator++()
{
	*(this) = *(this) + BigInt(1);
	return(*this);
}

BigInt BigInt::operator++(int)
{
	BigInt temp = (*this);
	*(this) = *(this) + BigInt(1);
	return(temp);
}


BigInt BigInt::operator<<(unsigned int n)const
{
	BigInt temp = *this;

	temp.str.insert(temp.str.end(), n, '0');
	//std::cout << temp.str << std::endl;
	return(temp);
}

BigInt BigInt::operator>>(unsigned int n)const
{
	BigInt temp = *this;
	size_t len = temp.str.length();
	if(n >= len)
		temp.str = "0";
	else
	{
		temp.str.erase(temp.str.length() - n, n); // ilk parametre: silme yapacağın yerin başlangıç indexi, diğeri: kaç tane eleman silinecek
	}
	return(temp);
}

BigInt& BigInt::operator<<=(unsigned int n)
{
	(*this) = (*this) << n;
	return(*this);
}

BigInt& BigInt::operator>>=(unsigned int n)
{
	(*this) = (*this) >> n;
	return(*this);
}

unsigned int stringToUINT(std::string str)
{
	std::stringstream ss(str);
	unsigned int res;
	ss >> res;
	return (res);
}

BigInt BigInt::operator<<(const BigInt& other)const
{
	BigInt temp;
	temp = (*this) << stringToUINT(other.str);
	return(temp);
}

BigInt BigInt::operator>>(const BigInt& other)const
{
	BigInt temp;
	temp = (*this) >> stringToUINT(other.str);
	return(temp);
}

BigInt& BigInt::operator<<=(const BigInt& other)
{
	(*this) = (*this) << stringToUINT(other.str);
	return(*this);
}

BigInt& BigInt::operator>>=(const BigInt& other)
{
	(*this) = (*this) >> stringToUINT(other.str);
	return(*this);
}


bool BigInt::operator==(const BigInt& other) const
{
	if(this->getStr() == other.getStr())
		return(true);
	return(false);
}

bool BigInt::operator!=(const BigInt& other) const
{
	return(!((*this) == (other)));
}

bool BigInt::operator<(const BigInt& other) const
{
	std::string str1 = this->str;
	std::string str2 = other.getStr();
	size_t len1 = str1.length();
	size_t len2 = str2.length();

	if(len1 != len2)
		return(len1 < len2);
	return(str1 < str2);  // thanks for your feedback, mjuicha!! o7
}

bool BigInt::operator>(const BigInt& other) const
{
	return(!(((*this) < other)));
}

bool BigInt::operator<=(const BigInt& other) const
{
	return((((*this) < other) || ((*this) == other)));
}

bool BigInt::operator>=(const BigInt& other) const
{
	return((((*this) > other) || ((*this) == other)));
}

// non member func
std::ostream& operator<<(std::ostream& output, const BigInt& obj)
{
	output << obj.getStr();
	return(output);
}
