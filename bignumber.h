#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include <vector>
#include <string>
#include <iostream>
#define UNIT_VAL 100000000
#define UNIT_LEN 8
class BigNumber {
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
        bool isanum() const;
        friend std::ostream& operator<<(std::ostream& os, const BigNumber& a);

    private:
        static void _add(const BigNumber& a, const BigNumber& b, BigNumber& res);// a + b, a, b same sig
        static void _sub(const BigNumber& a, const BigNumber& b, BigNumber& res);// a - b, abs(a) >= abs(b)
        static void _mul(const BigNumber& a, int b, BigNumber& res);
        static void _div(const BigNumber& a, int b, BigNumber& res);
        void _shiftup8();
        void _shiftdown8();
        void _remove_padding();
        std::vector<int> integer;
        long intLen;
        bool negative;
        bool isValid;
};

#endif
