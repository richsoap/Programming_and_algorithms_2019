#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H
#include <string>

class NumberGenerator {
    public:
        NumberGenerator();
        NumberGenerator(int len);
        NumberGenerator(int _left, int _right);
        std::string getNumber();
        void setInterval(int len);
        void setInterval(int _left, int _right);
    private:
        int left;
        int right;
};

#endif
