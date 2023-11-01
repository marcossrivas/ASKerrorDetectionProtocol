#pragma once
#include <stdint.h>

class CheckFormat
{
private:

    uint8_t lowData {};
    uint8_t highData {};

    //int checkSum {}; 
    //int dataParityBit {};
    //int checkSumParityBit {};

public:

    CheckFormat() : lowData(0) , highData(0) {}

    bool checkStop();
    bool checkStart();
    bool checkParity();
    bool checkSum();

    uint8_t getlowData();
    uint8_t gethighData();

    ~CheckFormat() {}

};