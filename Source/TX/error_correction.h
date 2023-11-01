#pragma once
#include <stdint.h>

class Checksum
{
private:

    int8_t lowData;
    int8_t highData;

    int checkSum; 
    int dataParityBit;
    int checkSumParityBit;
    int CheckSumCount;


public:

    Checksum() : lowData(0) , highData(0) {}

    void updateData(const int8_t& lowData,const int8_t& highData);
    int bitCounter();
    int dataParity();
    int checksumParity();






};