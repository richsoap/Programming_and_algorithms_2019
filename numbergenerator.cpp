#include "numbergenerator.h"
#include <cstdlib>
#include <iostream>
using namespace std;

NumberGenerator::NumberGenerator(): left(1), right(10) {}
NumberGenerator::NumberGenerator(int len) {
    setInterval(len);
}
NumberGenerator::NumberGenerator(int _left, int _right) {
    setInterval(_left, _right);
}

void NumberGenerator::setInterval(int len) {
    len = len>0?len:10;
    setInterval(1, len);
}

void NumberGenerator::setInterval(int _left, int _right) {
    left = _left;
    right = left<=_right?_right:left;
}

string NumberGenerator::getNumber() {
    int len;
    if(right != left)
        len = (rand() % (right - left)) + left;
    else
        len = left;
    string result(len, '0');
    for(auto& C:result)
        C += rand() % 10;
    return result;
}
