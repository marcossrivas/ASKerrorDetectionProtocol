#include "check_format.h"

void CheckFormat::initFormat(const uint8_t* buffer) //listo
{
    startByte = buffer[0];
    lowData = buffer[1];
    highData = buffer[2];
    stopByte = buffer[3];
}

void CheckFormat::extractRawData()
{
    rawLowData = lowData;
    rawHighData = (highData & 0b00000011);
}

int CheckFormat::bitCounter()//listo
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
   
    return dataBitCounter = (lowCounter + highCounter);
}

int CheckFormat::checkSumCounter()
{
    int CheckSumCount = 0;
    int checkSum = this->checkSumData;

    for(int i = 0; i<4; i++)
    {
        CheckSumCount += checkSum & 1;
        checkSum = checkSum >> 1;
    }

    return checkSumCt = CheckSumCount;
}

bool CheckFormat::checkStart()//listo
{
    if (startByte == 0b10101010) {return true;}
    else {return false;}
}

bool CheckFormat::checkParitydata()
{
    int dataParityBitTx;
    dataParityBit = (highData & 0b01000000) >> 6;

    if (dataBitCounter % 2 == 0) {dataParityBitTx = 0;}
    else {dataParityBitTx = 1;}

    if (dataParityBit == dataParityBitTx) {return true;}
    else {return false;}
}

bool CheckFormat::checkParityCheckSum()
{
    int checkSumParityBitTx;
    checkSumParityBit = (highData & 0b10000000) >> 7;

    if(checkSumCt %2 == 0){checkSumParityBitTx = 0;}
    else {checkSumParityBitTx = 1;}

    if (checkSumParityBit == checkSumParityBitTx) {return true;}
    else {return false;}
}

bool CheckFormat::checkParity()//falta estaaa
{
    if(checkParitydata() && checkParityCheckSum()) {return true;}
    else {return false;}
}

bool CheckFormat::checkSum()//listo
{
  checkSumData = (highData & 0b00111100) >> 2;
  if (checkSumData == dataBitCounter) {return true;}
  else {return false;}
}

bool CheckFormat::checkStop() //listo
{
    if (stopByte == 0b01010101) {return true;}
    else {return false;}
}

uint8_t CheckFormat::getlowData()//listo
{
    return rawLowData;
}

uint8_t CheckFormat::gethighData()//listo
{
    return rawHighData;
}