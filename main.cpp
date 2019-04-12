#include "bignumber.h"
#include "stopwatch.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
using namespace std;

static int main_0() {
    string inputFileName = "TestNumber.txt";
    string outputFileName = "TestOut.txt";

    fstream inFile, outFile;
    StopWatch stopwatch;
    long totalTime = 0;
    int totalCount = 0;
    timeval start, end;
    inFile.open(inputFileName, ios::in);
    outFile.open(outputFileName, ios::out);
    int testSize = 10000;
    vector<BigNumber> numberFront(testSize);
    vector<BigNumber> numberBack(testSize);
    vector<BigNumber> numberResult(testSize);
    string num0, num1;
    while(inFile) {
        int count;
        for(count = 0;count < testSize && inFile;count ++) {
            inFile>>num0>>num1;
            numberFront[count] = BigNumber(num0);
            numberBack[count] = BigNumber(num1);
        }
        totalCount += count;
        stopwatch.start();
        for(int i = 0;i < count;i ++) {
            // Do Something here, Like
            //numberResult[i] = numberFront[i] + numberBack[i];
        }
        totalTime += stopwatch.pause();
        for(int i = 0;i < count;i ++)
            outFile<<numberFront[i]<<"  "<<numberBack[i]<<"  "<<numberResult[i]<<endl;
    }
    outFile.close();
    inFile.close();
    cout<<"Total time: "<<totalTime<<endl<<"Case count: "<<totalCount<<endl<<"Average time: "<<totalTime/totalCount<<endl;
    return 0;
}

static int main_1() {
    string input0, input1, cacu;
    while(cin>>input0>>cacu>>input1) {
        BigNumber num0(input0);
        BigNumber num1(input1);
        BigNumber result;
        switch(cacu[0]) {
            case '+': result = num0 + num1;
                      break;
            case '-': result = num0 - num1;
                      break;
            case '*': result = num0 * num1;
                      break;
            case '/': result = num0 / num1;
                      break;
            default:cout<<"Wrong cacu!!"<<endl;
        }
        cout << num0<<" "<<cacu<<" " << num1<<" = "<<result<<endl;
    }
    return 0;
}

int main() {
    return main_1();
}
