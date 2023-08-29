#include<iostream>
#include"./SPNExample.h"
using namespace std;

SPNExamples spn;

void printSNPData(char* data, int amount){
    for(int i = 0; i < amount; i++){
        cout << *(data + i);
    }
}
void SNPCharEncryption(char* data, int amount){
    for(int i = 0; i < amount; i++){
        data[i] = spn.charEncryption(data[i]);
    }
}
void SNPCharDecrypt(char* data, int amount){
    for(int i = 0; i < amount; i++){
        data[i] = spn.charDecrypt(data[i]);
    }
}

int main(){
    const int dataAmount = 1;
    char* data = new char[dataAmount];

    cout << "Input your string = " ;
    for(int i = 0; i < dataAmount; i++){
        cin >> data[i];
    }
    
    cout << "==============================" << endl;

    // charEncryption
    SNPCharEncryption(data, dataAmount);
    cout << "charEncryption string = " ;
    printSNPData(data, dataAmount);
    cout << endl;

    // charDecrypt
    SNPCharDecrypt(data, dataAmount);
    cout << "charDecrypt string = " ;
    printSNPData(data, dataAmount);
    cout << endl;

    return 0;
}