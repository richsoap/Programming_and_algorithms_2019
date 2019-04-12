#include "bignumber.h"
#include "stopwatch.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
using namespace std;

static void Test0() {
    vector<string> src(6);
    src[0] = "123456789100200300400500600700800900";
    src[1] = src[0] + ".0123456789";
    src[2] = src[1] + "0000000";
    src[3] = src[0] + ".";
    src[4] = "." + src[0];
    src[5] = "-" + src[0];
    for(const auto& str:src) {
        BigNumber val(str);
        cout<<str<<endl<<val<<endl;
        cout<<"pass"<<endl;
    }
        
}

static void Test1() {
    /*vector<string> src(7);
    src[1] = "1";
    src[1] = src[0] + ".9999985";
    src[2] = "0.0000215";
    src[3] = "-" + src[0];
    src[4] = "-" + src[2];
    src[5] = "999999999.999999999999999999999999999999999999999";
    src[6] = "0.00000000000000000000000000000000000000000000000000000001";
    */

    vector<string> src(2);
    src[0] = "451303014887266313";
    src[1] = "4707";

    /*
    vector<string> src(10);
    src[0] = "0.1";
    src[1] = "0.01";
    src[2] = "0.001";
    src[3] = "0.0001";
    src[4] = "0.00001";
    src[5] = "0.000001";
    src[6] = "0.0000001";
    src[7] = "0.00000001";
    src[8] = "0.000000001";
    src[9] = "0.0000000001";
    */
    for(const auto& a:src) {
        for(const auto& b:src) {
            BigNumber n0(a);
            BigNumber n1(b);
            cout<<a<<" "<<b<<endl;
            cout<<n0<<" "<<n1<<endl;
            BigNumber res = n0 + n1;
            cout<<res<<endl;
            res = n0 - n1;
            cout<<res<<endl;
            res = n1 - n0;
            cout<<res<<endl<<endl;
        }
    }

}

static void Test2() {
    vector<string> src(4);
    src[0] = "1.1";
    src[1] = "22222222.22222222";
    src[2] = "-" + src[0];
    src[3] = "-" + src[0];
    
    
    int n = src.size();
    for(int i = 0;i < n;i ++) {
        for(int j = i + 1;j < n;j ++) {
            cout<<src[i]<<"*"<<src[j]<<endl;
            BigNumber n0(src[i]), n1(src[j]);
            BigNumber res = n0 * n1;
            cout<<res<<endl;
        }
    }
}

static void Test3() {
    string inputFileName = "TestNumber.txt";
    string outputFileName = "TestOut.txt";

    fstream inFile, outFile;
    StopWatch stopwatch;
    long timeUse = 0;
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
        timeUse += stopwatch.pause();
        for(int i = 0;i < count;i ++)
            outFile<<numberFront[i]<<"  "<<numberBack[i]<<"  "<<numberResult[i]<<endl;
    }
    outFile.close();
    inFile.close();
    cout<<"Total time: "<<totalTime<<endl<<"Case count: "<<totalCount<<endl<<"Average time: "<<totalTime/totalCount<<endl;
}

static void Test4() {
    fstream inFile, sizeFile;
    long result = 0;
    timeval start, end;
    sizeFile.open("TestSize.txt", ios::in);
    inFile.open("TestNumber.txt", ios::in);
    string num0, num1;
    int len, nSize;
    BigNumber res;
    while(sizeFile>>len>>nSize) {
        vector<vector<string>> testInput(2, vector<string>(nSize));
        cout<<len<<endl;
        for(int i = 0;i < nSize;i ++)
            inFile>>testInput[0][i]>>testInput[1][i];
        gettimeofday(&start, NULL);
        for(int i = 0;i < nSize;i ++) {
            BigNumber bNum0(testInput[0][i]);
            BigNumber bNum1(testInput[1][i]);
            res = bNum0 + bNum1;
        }
        gettimeofday(&end, NULL);
        result += end.tv_usec - start.tv_usec + 1000000 * (end.tv_sec - start.tv_sec);
        cout<<result<<" "<<result/nSize<<endl;
        gettimeofday(&start, NULL);
        for(int i = 0;i < nSize;i ++) {
            BigNumber bNum0(testInput[0][i]);
            BigNumber bNum1(testInput[1][i]);
            res = bNum0 - bNum1;
        }
        gettimeofday(&end, NULL);
        result += end.tv_usec - start.tv_usec + 1000000 * (end.tv_sec - start.tv_sec);
        cout<<result<<" "<<result/nSize<<endl;
        gettimeofday(&start, NULL);
        for(int i = 0;i < nSize;i ++) {
            BigNumber bNum0(testInput[0][i]);
            BigNumber bNum1(testInput[1][i]);
            res = bNum0 * bNum1;
        }
        gettimeofday(&end, NULL);
        result += end.tv_usec - start.tv_usec + 1000000 * (end.tv_sec - start.tv_sec);
        cout<<result<<" "<<result/nSize<<endl;
        gettimeofday(&start, NULL);
        for(int i = 0;i < nSize;i ++) {
            BigNumber bNum0(testInput[0][i]);
            BigNumber bNum1(testInput[1][i]);
            res = bNum0 / bNum1;
        }
        gettimeofday(&end, NULL);
        result += end.tv_usec - start.tv_usec + 1000000 * (end.tv_sec - start.tv_sec);
        cout<<result<<" "<<result/nSize<<endl;
        cout<<"---------------------------------"<<endl;
    }
    sizeFile.close();
    inFile.close();
}



int main() {
    Test3();
    return 0;
}
