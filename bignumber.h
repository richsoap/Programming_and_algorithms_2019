#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include <vector>
#include <string>
#include <iostream>
#define UNIT_VAL 100000000
#define UNIT_LEN 8
class BigNumber {
    // 请补写出以下函数
    public:
        BigNumber();
        BigNumber(const std::string& str);
        BigNumber(const BigNumber& a);
        BigNumber operator +(const BigNumber& a);
        BigNumber operator -(const BigNumber& a);
        BigNumber operator *(const BigNumber& a);
        BigNumber operator /(const BigNumber& a);
        bool operator <(const BigNumber& a);
        bool operator ==(const BigNumber& a);
        friend std::ostream& operator<<(std::ostream& os, const BigNumber& a);
};

#endif
