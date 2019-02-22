#include "bignumber.h"
#include <iomanip>
#include <algorithm>
using namespace std;
BigNumber::BigNumber() {}
BigNumber::BigNumber(const string& str) {
}

BigNumber::BigNumber(const BigNumber& a):intLen(a.intLen), negative(a.negative) {
}

ostream& operator<<(ostream& os, const BigNumber& a) {
}

bool BigNumber::operator < (const BigNumber& a) {
}

bool BigNumber::operator == (const BigNumber& a) {
}

BigNumber BigNumber::operator +(const BigNumber& a) {
}

BigNumber BigNumber::operator -(const BigNumber& a) {
}

BigNumber BigNumber::operator *(const BigNumber& a) {
}

BigNumber BigNumber::operator /(const BigNumber& a) {
}
