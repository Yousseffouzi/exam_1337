#include <iostream>
#include <string>

class BigInt
{
    private:
        std::string digits;

        std::string addStrs(const std::string& a, const std::string& b) const;
        bool isZero() const;
        void removeZeros();
        bool checkDigits(const std::string& s) const;
        
    public:
        BigInt();
        BigInt(unsigned int nbr);
        BigInt(const std::string& nbr);
        
        BigInt operator+(const BigInt& other) const;
        BigInt& operator+=(const BigInt& other);
        
        bool operator==(const BigInt& other) const;
        bool operator!=(const BigInt& other) const;
        bool operator<(const BigInt& other) const;
        bool operator>(const BigInt& other) const;
        bool operator<=(const BigInt& other) const;
        bool operator>=(const BigInt& other) const;
        
        BigInt operator<<(unsigned int shift) const;
        BigInt operator>>(unsigned int shift) const;
        BigInt& operator<<=(unsigned int shift);
        BigInt& operator>>=(unsigned int shift);

        BigInt& operator<<=(const BigInt& shift);
        BigInt& operator>>=(const BigInt& shift);
        
        BigInt& operator++();
        BigInt operator++(int);
        
        std::string getDigits() const;
};

std::ostream& operator<<(std::ostream& out, const BigInt& nbr);