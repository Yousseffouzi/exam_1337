#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class BigInt {
private:
    std::string num;

public:
    BigInt(size_t n) : num(std::to_string(n)) {}
    BigInt() : num("0") {}

    BigInt(const BigInt& oth) : num(oth.num) {}

    BigInt(const std::string& n) {
        if (n.empty() || !std::all_of(n.begin(), n.end(), ::isdigit) || (n.size() > 1 && n[0] == '0')) {
            std::cout << "Invalid number string" << std::endl;
            num = "0";
        }
        else
            num = n;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& b) {
        return os << b.num;
    }

    std::string add_strings(const std::string& n1, const std::string& n2) const {
        std::string result;
        int carry = 0, i = n1.size() - 1, j = n2.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            int sum = (i >= 0 ? n1[i--] - '0' : 0) + (j >= 0 ? n2[j--] - '0' : 0) + carry;
            result.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        std::reverse(result.begin(), result.end());
        i = 0;
        while (result[i] == '0')
            i++;
        result = result.substr(i, result.size());
        return result;
    }

    BigInt operator+(const BigInt& oth) const {
        return BigInt(add_strings(num, oth.num));
    }

    BigInt& operator+=(const BigInt& oth) {
        num = add_strings(num, oth.num);
        return *this;
    }

    BigInt& operator++() {
        return *this += BigInt(1);
    }

    BigInt operator++(int) {
        BigInt tmp(*this);
        ++(*this);
        return tmp;
    }

    BigInt operator<<(size_t shift) const {
        return BigInt(num + std::string(shift, '0'));
    }

    BigInt& operator<<=(size_t shift) {
        num += std::string(shift, '0');
        return *this;
    }

    BigInt& operator>>=(const BigInt& b) {
        if (BigInt(num.size()) <= b)
            num = "0";
        else {
            BigInt i(0);
            while (i < b) {
                num = num.substr(0, num.size() - 1);
                ++i;
            }
        }
        return *this;
    }

    bool operator<(const BigInt& oth) const {
        if (num.size() < oth.num.size())
            return 1;
        else if (num.size() > oth.num.size())
            return 0;
        return num < oth.num;
    }

    bool operator>(const BigInt& oth) const {
        return oth < *this;
    }

    bool operator==(const BigInt& oth) const {
        return num == oth.num;
    }

    bool operator!=(const BigInt& oth) const {
        return num != oth.num;
    }

    bool operator<=(const BigInt& oth) const {
        return !(*this > oth);
    }

    bool operator>=(const BigInt& oth) const {
        return !(*this < oth);
    }

    // step 6: extra test
    BigInt operator-(const BigInt& oth) const {
        (void) oth;
        return BigInt();
    }
};
