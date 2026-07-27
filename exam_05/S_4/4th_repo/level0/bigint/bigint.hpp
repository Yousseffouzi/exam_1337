/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatkeski <fatkeski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:17:26 by fatkeski          #+#    #+#             */
/*   Updated: 2025/08/01 13:57:18 by fatkeski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BigInt
#define BigInt

#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>

class BigInt
{
	private:
		std::string str;
		//std::string result;
	public:
		BigInt();
		BigInt(unsigned int num);
		BigInt(const BigInt& source);

		std::string getStr()const;

		BigInt& operator=(const BigInt& source);

		// addition
		BigInt operator+(const BigInt& other)const;
		BigInt& operator+=(const BigInt& other);

		// increments
		BigInt& operator++(); // ++x
		BigInt operator++(int); // x++

		// shift with num
		BigInt operator<<(unsigned int n)const;
		BigInt operator>>(unsigned int n)const;
		BigInt& operator<<=(unsigned int n);
		BigInt& operator>>=(unsigned int n);

		//shift with object
		BigInt operator<<(const BigInt& other)const;
		BigInt operator>>(const BigInt& other)const;
		BigInt& operator<<=(const BigInt& other);
		BigInt& operator>>=(const BigInt& other);

		// ==, !=, <, >, <=, >=
		bool operator==(const BigInt& other) const;
		bool operator!=(const BigInt& other) const;
		bool operator<(const BigInt& other) const;
		bool operator>(const BigInt& other) const;
		bool operator<=(const BigInt& other) const;
		bool operator>=(const BigInt& other) const;

		// ~BigInt();

};

std::ostream& operator<<(std::ostream& output, const BigInt& obj);

#endif
