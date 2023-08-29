/*
    SPN加密實做
    設計者:KennyLin
    日期:2022/1/9
    版本:V1.0.1
    開始修改 : 2023/8/28 00:00
    deadline : none
    結束修改 : 2023/8/29 15:46

    fix bug:
    1. code refactoring
        values and functions rename -- done
            rename class SPN_255 to SNPExamples
            rename encryption and decrypt to charEncryption and charDecrypt
            others
        move tmpValues to functions -- done // Don't put tmp in class member
        using map STL for S/P Boxes and Keys -- done
    2. change charEncryption and charDecrypt function parameters to unsigned char -- done
*/

// #include<iostream>
#include<cmath>
#include<map>
using namespace std;

class SPNExamples{
    public:
    unsigned char charEncryption(unsigned char);
    unsigned char charDecrypt(unsigned char);

    private:
    map<int, int> keys = {
        {0, 0xee},
        {1, 0x44},
        {2, 0x19}
    };
    map<int, int> sBox = {
        {0, 1},
        {1, 3},
        {2, 5},
        {3, 7},
        {4, 9},
        {5, 11},
        {6, 13},
        {7, 15},
        {8, 2},
        {9, 4},
        {10, 6},
        {11, 8},
        {12, 10},
        {13, 12},
        {14, 14},
        {15, 0}
    };
    map<int, int> sBoxReveres = {
        {sBox[0], 0},
        {sBox[1], 1},
        {sBox[2], 2},
        {sBox[3], 3},
        {sBox[4], 4},
        {sBox[5], 5},
        {sBox[6], 6},
        {sBox[7], 7},
        {sBox[8], 8},
        {sBox[9], 9},
        {sBox[10], 10},
        {sBox[11], 11},
        {sBox[12], 12},
        {sBox[13], 13},
        {sBox[14], 14},
        {sBox[15], 15},
    };
    map<int, int> pBox = {
        {0, 2},
        {1, 3},
        {2, 0},
        {3, 4},
        {4, 1},
        {5, 7},
        {6, 5},
        {7, 6}
    };
    map<int, int> pBoxReveres = {
        {pBox[0], 0},
        {pBox[1], 1},
        {pBox[2], 2},
        {pBox[3], 3},
        {pBox[4], 4},
        {pBox[5], 5},
        {pBox[6], 6},
        {pBox[7], 7},
    };

    bool* setBitsTmp(int, int);
    int setBitsNum(bool*, int, int);
    bool* resetBitsTmp(int*, int, int);
};

unsigned char SPNExamples::charEncryption(unsigned char data){
    const int charBits = 8;
    int numTmp = (int)data;
    bool *bitsTmp;
    int bitsNum[2];

    for (int i = 0; i < 3; i++)
    {
        bitsTmp = setBitsTmp(numTmp, charBits);
        
        // S Box implementation
        bitsNum[0] = sBox[setBitsNum(bitsTmp, 0, 4)];
        bitsNum[1] = sBox[setBitsNum(bitsTmp, 4, 7)];
        delete bitsTmp;
        bitsTmp = resetBitsTmp(bitsNum, 4, 2);

        // P Box implementation
        bool bitsTmp2[charBits];
        for (int j = 0; j < charBits; j++){
            bitsTmp2[pBox[j]] = bitsTmp[j];
        }
        for (int j = 0; j < charBits; j++){
            bitsTmp[j] = bitsTmp2[j];
        }
        numTmp = setBitsNum(bitsTmp, 0, charBits);

        numTmp ^= keys[i];

        delete bitsTmp;
    }
    return (unsigned char)numTmp;
}
unsigned char SPNExamples::charDecrypt(unsigned char data){
    const int charBits = 8;
    int numTmp = (int)data;
    bool* bitsTmp;
    int bitsNum[2];

    for (int i = 2; i >= 0; i--){
        numTmp ^= keys[i];

        // P Box implementation
        bitsTmp = setBitsTmp(numTmp, charBits);
        bool bitTmp[charBits];
        for (int j = 0; j < charBits; j++){
            bitTmp[pBoxReveres[j]] = bitsTmp[j];
        }
        for (int j = 0; j < charBits; j++){
            bitsTmp[j] = bitTmp[j];
        }

        // S Box implementation
        bitsNum[0] = sBoxReveres[setBitsNum(bitsTmp, 0, 4)];
        bitsNum[1] = sBoxReveres[setBitsNum(bitsTmp, 4, 4)];
        delete bitsTmp;
        bitsTmp = resetBitsTmp(bitsNum, 4, 2);
        numTmp = setBitsNum(bitsTmp, 0, charBits);

        delete bitsTmp;
    }
    return (unsigned char)numTmp;
}

bool* SPNExamples::setBitsTmp(int numData, int digits){
    bool *tmp = new bool[digits];
    for (int i = 0; i < digits; i++)
    {
        int tmpBits = numData % 2;
        tmp[i] = tmpBits;
        numData /= 2;
    }
    return tmp;
}
int SPNExamples::setBitsNum(bool *bitsData, int begin, int bits)
{
    int tmp = 0; // 必須歸0
    // cout << "tmp1 = " << tmp << endl;
    for(int i = 0; i < bits; i++){
        tmp += bitsData[begin + i] * pow(2, i);
    }
    // cout << "tmp2 = " << tmp << endl;
    return tmp;
}

bool * SPNExamples::resetBitsTmp(int *bitsNum, int arrayBits, int round)
{
    bool *tmp = new bool[arrayBits * round];
    for(int i = 0; i < round; i++){
        bool *roundBits = setBitsTmp(bitsNum[i], arrayBits);
        for(int j = 0; j < arrayBits; j++){
            tmp[arrayBits * i + j] = roundBits[j];
        }
        delete roundBits;
    }
    return tmp;
}
