#include "bignumber.h"
#include <iomanip>
#include <algorithm>
using namespace std;
BigNumber::BigNumber():intLen(0), negative(false),isValid(true) {}
BigNumber::BigNumber(const string& str) {
    int offset = 0;
    int len = str.length();
    isValid = true;
    if(str[0] == '-') {
        offset ++;
        negative = true;
    }
    else
        negative = false;
    intLen = str.length() - offset;
    intLen = intLen % UNIT_LEN != 0?intLen/8+1:intLen/8;
    integer = vector<int>(intLen,0);
    for(int i = 0;i < intLen;i ++) {
        int durOffset = (len - offset) % 8;
        if(durOffset == 0)
            durOffset = 8;
        for(int j = 0;j < durOffset;j ++)
            integer[i] = integer[i] * 10 + str[offset ++] - '0';
    }
    reverse(integer.begin(), integer.end());
    _remove_padding();
}

BigNumber::BigNumber(const BigNumber& a):intLen(a.intLen), negative(a.negative) {
    integer.assign(a.integer.begin(), a.integer.end());
}
bool BigNumber::isanum() const {
    return isValid;
}

ostream& operator<<(ostream& os, const BigNumber& a) {
    if(!a.isanum()) {
        os << "NaN";
        return os;
    }
    os<<setfill('0');
    if(a.negative && a.intLen )
        os<<'-';
    if(a.intLen == 0)
        os<<0;
    else {
        os<<a.integer[a.intLen - 1];
        for(int i = a.intLen - 2;i >= 0;i --)
            os<<setw(8)<<a.integer[i];
    }
    return os;
}

bool BigNumber::operator < (const BigNumber& a) {
    if(negative ^ a.negative) {
        if(negative)
            return true;
        else
            return false;
    }
    bool res = true;
    int index = 0;
    if(intLen == a.intLen) {
        for(index = intLen - 1;index >= 0 && integer[index] == a.integer[index];index --);
        if(index == -1)
            res = false;
        else
            res = integer[index] < a.integer[index];
    }
    else
        res = intLen < a.intLen;
    if(negative)
        return !res;
    else
        return res;
}

bool BigNumber::operator == (const BigNumber& a) {
    bool res = a.intLen == intLen;
    for(int i = intLen - 1;i >= 0 && res;i --)
        res = integer[i] == a.integer[i];
    return res;
}

BigNumber BigNumber::operator +(const BigNumber& a) {
    BigNumber res;
    if(negative ^ a.negative) {
        if(negative) {
            negative = !negative;
            if(*this < a) {
                _sub(a, *this, res);
                res.negative = false;
            }
            else {
                _sub(*this, a, res);
                res.negative = true;
            }
            negative = !negative;
        }
        else {
            negative = !negative;
            if(*this < a) {
                _sub(*this, a, res);
                res.negative = false;
            }
            else {
                _sub(a, *this, res);
                res.negative = true;
            }
            negative = !negative;
        }
    }
    else {
        _add(*this, a, res);
        res.negative = negative;
    }
    res._remove_padding();
    return res;
}

BigNumber BigNumber::operator -(const BigNumber& a) {
    BigNumber res;
    if(negative ^ a.negative) {
        _add(*this, a, res);
        res.negative = negative;
    }
    else {
        if(negative) {
            if(*this < a) {
                _sub(*this, a, res);
                res.negative = true;
            }
            else {
                _sub(a, *this, res);
                res.negative = false;
            }
        }
        else {
            if(*this < a) {
                _sub(a, *this, res);
                res.negative = true;
            }
            else {
                _sub(*this, a, res);
                res.negative = false;
            }
        }
    }
    res._remove_padding();
    return res;
}

BigNumber BigNumber::operator *(const BigNumber& a) {
    BigNumber res;
    BigNumber temp = a;
    for(int i = 0;i < intLen;i ++) {
        BigNumber temp_res;
        _mul(temp, integer[i], temp_res);
        res = res + temp_res;
        temp._shiftup8();
    }
    res.negative = negative ^ a.negative;
    res._remove_padding();
    return res;
}

BigNumber BigNumber::operator /(const BigNumber& a) {
    BigNumber res;
    if(*this < a)
        return res;
    if(a.intLen == 0) {
        res.isValid = false;
        return res;
    }
    res.intLen = intLen - a.intLen + 1;
    res.integer = vector<int>(res.intLen, 0);
    BigNumber tA = a;
    BigNumber tT = *this;
    for(int i = 1;i < res.intLen;i ++)
        tA._shiftup8();
    for(int i = res.intLen - 1;i >= 0;i --) {
        int headVal = 0;
        for(int i = tT.intLen - 1;i >= tA.intLen -1;i --)
            headVal = headVal * UNIT_VAL + tT.integer[i];
        int maxVal = headVal / tA.integer[tA.intLen - 1];
        int minVal = headVal / (tA.integer[tA.intLen - 1] + 1);
        BigNumber tRes;
        while(minVal < maxVal) {
            int midVal = (minVal + maxVal) / 2;
            if(midVal == minVal)
                midVal ++;
            _mul(tA,  midVal, tRes);
            if(tRes < tT)
                minVal = midVal;
            else if(tRes == tT) {
                minVal = midVal;
                maxVal = midVal;
            }
            else {
                if(midVal == maxVal)
                    maxVal = minVal;
                else
                    maxVal = midVal;
            }
        }
        res.integer[i] = maxVal;
        tT = tT - tRes;
        tA._shiftdown8();
    }
    res.negative = a.negative ^ negative;
    res._remove_padding();
    return res;
}

void BigNumber::_add(const BigNumber&a, const BigNumber&b, BigNumber&res) {
    long long pre = 0;
    res.intLen = max(a.intLen, b.intLen);
    res.integer = vector<int>(res.intLen, 0);
    for(int i = 0;i < res.intLen;i ++) {
        if(i < a.intLen)
            pre += a.integer[i];
        if(i < b.intLen)
            pre += b.integer[i];
        res.integer[i] = pre % UNIT_VAL;
        pre /= UNIT_VAL;
    }
    if(pre) {
        res.integer.push_back(pre);
        res.intLen ++;
    }
    res._remove_padding();
}

void BigNumber::_sub(const BigNumber& a, const BigNumber& b, BigNumber& res) {
    long long pre = 0;
    res.intLen = max(a.intLen, b.intLen);
    res.integer = vector<int>(res.intLen, 0);
    for(int i = 0;i < res.intLen;i ++) {
        if(i < a.intLen)
            pre += a.integer[i];
        if(i < b.intLen)
            pre -= b.integer[i];
        if(pre < 0) {
            res.integer[i] = pre + UNIT_VAL;
            pre = -1;
        }
        else {
            res.integer[i] =  pre;
            pre = 0;
        }
    }
    res._remove_padding();
}

void BigNumber::_mul(const BigNumber& a, int b, BigNumber& res) {
    res.intLen = a.intLen;
    res.integer = vector<int>(res.intLen);
    long long pre = 0;
    for(int i = 0;i < res.intLen;i ++) {
        pre += (long long)a.integer[i] * b;
        res.integer[i] = pre % UNIT_VAL;
        pre /= UNIT_VAL;
    }
    if(pre) {
        res.integer.push_back(pre);
        res.intLen ++;
    }
    res._remove_padding();
}

void BigNumber::_div(const BigNumber& a, int b, BigNumber& res) {
    if(b == 0)
        return;
    long long pre = 0;
    res.negative = b < 0 ^ a.negative;
    res.intLen = a.intLen;
    res.integer = vector<int>(res.intLen);
    for(int i = res.intLen - 1;i >= 0;i --) {
        pre *= UNIT_VAL;
        pre += a.integer[i];
        res.integer[i] = pre / b;
        pre %= b;
    }
    int count = 300;
}


void BigNumber::_shiftup8() {
    if(intLen) {
        integer.insert(integer.begin(), 0);
        intLen ++;
    }
}

void BigNumber::_shiftdown8() {
    if(intLen) {
        integer.erase(integer.begin());
        intLen --;
    }
}

void BigNumber::_remove_padding() {
    while(intLen && integer[intLen - 1] == 0)
        intLen --;
    if(intLen == 0)
        negative = false;
}
