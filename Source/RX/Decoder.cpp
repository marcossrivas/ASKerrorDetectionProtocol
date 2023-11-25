#include "Decoder.h"

// Propósito de cada método anunciado en header.

void Decoder::extractRawData()
{
    rawLowData = lowData;
    rawHighData = (highData & 0b00000011); // AND bit a bit con mascara 00000011 para extraer informacion en esa posicion.
}

int Decoder::bitCounter()
{
    // Cuento bits parte baja.
    int lowCounter = 0;
    uint8_t lowData = this->lowData; 

    for(int i = 0; i < 8; i++)
    { 
        lowCounter += lowData & 1;
        lowData = lowData >> 1;
    }

    // Cuento bits parte alta.
    int highCounter = 0;
    uint8_t highData = this->highData; 
    
    for(int i = 0; i < 2; i++)
    {
        highCounter += highData & 1;
        highData = highData >> 1;
    }
   
    return dataBitCounter = (lowCounter + highCounter);
}

int Decoder::extractCheckSum()
{
    return checkSumData = (highData & 0b00111100) >> 2; // AND bit a bit con máscara 00111100 para extraer información en esa posición & Desplazamiento hacia a la der. x2.
}

int Decoder::checkSumCounter()
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

//// --- Métodos de control de error --- ////

bool Decoder::checkStart()
{
    if (startByte == 0b10101010) {return true;}
    else {return false;}
}

bool Decoder::checkSum()
{
  if (checkSumData == dataBitCounter) {return true;} // Comparo el valor extraído del checksum con la suma de '1' recibidos.
  else {return false;}
}

bool Decoder::checkParitydata() 
{
    dataParityBit = (highData & 0b01000000) >> 6; // Extraigo bit de paridad.

    if ((dataBitCounter + dataParityBit) % 2 == 0) {return true;} // Verifico paridad.
    else {return false;}
}

bool Decoder::checkParityCheckSum() 
{
    checkSumParityBit = (highData & 0b10000000) >> 7; // Extraigo bit de paridad.

    if((checkSumCt + checkSumParityBit) % 2 == 0) {return true;} // Verifico paridad.
    else {return false;}
}

bool Decoder::checkParity()
{
    if(checkParitydata() && checkParityCheckSum()) {return true;}
    else {return false;}
}

bool Decoder::checkStop() 
{
    if (stopByte == 0b01010101) {return true;}
    else {return false;}
}

void Decoder::init(const uint8_t* buffer) 
{
    startByte = buffer[0];
    highData = buffer[1];
    lowData = buffer[2];
    stopByte = buffer[3];

    extractRawData();
    bitCounter();
    extractCheckSum();
    checkSumCounter();
    checkParitydata();
    checkParityCheckSum();
}

uint8_t Decoder::getlowData()
{
    return rawLowData;
}

uint8_t Decoder::gethighData()
{
    return rawHighData;
}