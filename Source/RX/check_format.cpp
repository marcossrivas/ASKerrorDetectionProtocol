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

bool CheckFormat::checkStart()//listo
{
    if (startByte == 0b10101010) {return true;}
    else {return false;}
}

bool CheckFormat::checkParity()//falta estaaa
{
    dataParityBit = (highData & 0b01000000) >> 6;
    checkSumParityBit = (highData & 0b10000000) >> 7;

///////////////////check parity again...
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