#include "error_correction.h"

int Checksum::bitCounter()
{
    int lowCounter = 0;
    uint8_t lowData = this->lowData; //cuento bits parte baja

    for(int i = 0; i < 8; i++)
    { 
        lowCounter += lowData & 1;
        lowData = lowData >> 1;
    }

    int highCounter = 0;
    uint8_t highData = this->highData; //cuento bits parte alta
    
    for(int i = 0; i < 2; i++)
    {
        highCounter += highData & 1;
        highData = highData >> 1;
    }
    
    return checkSum = (lowCounter + highCounter);
}

int Checksum::dataParity()
{
    if (checkSum % 2 == 0) {dataParityBit = 0;}
    else {dataParityBit = 1;}

    return dataParityBit;
}

int Checksum::checksumParity()
{
    int CheckSumCount = 0;
    int checkSum = this->checkSum;

    for(int i = 0; i<4; i++)
    {
        CheckSumCount += checkSum & 1;
        checkSum = checkSum >> 1;
    }

    if(CheckSumCount %2 == 0){checkSumParityBit = 0;}
    else {checkSumParityBit = 1;}

    return checkSumParityBit;
}

void Checksum::updateData(const uint8_t& lowData,const uint8_t& highData)
{
    this->lowData = lowData;
    this->highData = highData;
    bitCounter();
    dataParity();
    checksumParity();
}

uint8_t Checksum::getlowData()
{
    return lowData;
}

uint8_t Checksum::gethighData()
{
    uint8_t highData = (checkSumParityBit * 128) + (dataParityBit * 64) + (checkSum * 4) + this->highData;
    return highData;
}

