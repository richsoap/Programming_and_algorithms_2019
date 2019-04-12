#include "numbergenerator.h"
#include <fstream>
#include <iostream>
#include <string>
#include <random>
using namespace std;
int main() {
    cout<<"min length, max length, num"<<endl;
    int minlen, maxlen, count;
    cin>>minlen>>maxlen>>count;
    default_random_engine engine;
    NumberGenerator generator(minlen,maxlen);
    while(count --) {
        cout<<generator.getNumber();
        switch(engine() % 4) {
            case 0: cout<<" + ";
                    break;
            case 1: cout<<" - ";
                    break;
            case 2: cout<<" * ";
                    break;
            case 3: cout<<" / ";
                    break;
        }
        cout<<generator.getNumber()<<endl;
    }
    return 0;
}
