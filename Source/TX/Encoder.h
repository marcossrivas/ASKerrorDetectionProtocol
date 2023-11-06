#pragma once
#include <stdint.h>

class Encoder
{
private:

    uint8_t lowData {};
    uint8_t highData {};

    int checkSum {}; 
    int dataParityBit {};
    int checkSumParityBit {};

public:

    Encoder() : lowData(0) , highData(0) {}

    void updateData(const uint8_t& lowData,const uint8_t& highData);
    int bitCounter();
    int dataParity();
    int checksumParity();

    uint8_t getlowData();
    uint8_t gethighData();

    ~Encoder() {}

};