#include "error_correction.h"

void Checksum::updateData(const int8_t& lowData,const int8_t& highData)
{
    this->lowData = lowData;
    this->highData = highData;
}

int Checksum::bitCounter()
{
    int lowCounter = 0;
    int8_t lowData = this->lowData; //cuento bits parte baja

    for(int i = 0; i < 8; i++)
    { 
        lowCounter += lowData & 1;
        lowData = lowData >> 1;
    }

    int highCounter = 0;
    int8_t highData = this->highData; //cuento bits parte alta
    
    for(int i = 0; i < 2; i++)
    {
        highCounter += highData & 1;
        highData = highData >> 1;
    }
    
    return checkSum = lowCounter + highCounter;
}

int Checksum::dataParity()
{
    if (checkSum % 2 == 0) {dataParityBit = 0;}
    else {dataParityBit =1;}
}

int Checksum::checksumParity()
{
    int checkSum = this->checkSum;

    for(int i = 0; i<4; i++)
    {
        CheckSumCount += checkSum & 1;
        checkSum = checkSum >> 1;
    }

    if(CheckSumCount %2 == 0){checkSumParityBit = 0;}
    else {checkSumParityBit = 1;}

    return CheckSumCount , checkSumParityBit;
}

int8_t Checksum::getlowData()
{
    return lowData;
}

int8_t Checksum::gethighData()
{
    return highData = (CheckSumCount*64) + (checkSum*4) + highData;
}

