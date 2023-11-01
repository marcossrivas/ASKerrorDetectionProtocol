/*#include <stdint.h>
#include<iostream>
#include<bitset>

class Checksum
{
private:
    static uint8_t lowData;
    static uint8_t highData;
    static int checkSum; 
    static int dataParityBit;
    static int checkSumParityBit;
    static int CheckSumCount;

public:
    void updateData();
    int calculateChecksum();
    int calculateDataParity();
    int calculateChecksumParity();
    static uint8_t getlowData();
    static uint8_t gethighData();

    ~Checksum() {}
};

uint8_t Checksum::lowData = 0;
uint8_t Checksum::highData = 0;
int Checksum::checkSum = 0;
int Checksum::dataParityBit = 0;
int Checksum::checkSumParityBit = 0;
int Checksum::CheckSumCount = 0;


void Checksum::updateData()
{
    lowData = 0b11101011;
    highData = 0b00000010;
}

int Checksum::calculateChecksum()
{
    // Calculate checksum and return it
    int lowCounter = 0;
    uint8_t lowData = Checksum::lowData;

    for(int i = 0; i < 8; i++)
    { 
        lowCounter += lowData & 1;
        lowData = lowData >> 1;
    }

    int highCounter = 0;
    uint8_t highData = Checksum::highData;

    for(int i = 0; i < 2; i++)
    {
        highCounter += highData & 1;
        highData = highData >> 1;
    }

    checkSum = lowCounter + highCounter;
    return checkSum;
}

int Checksum::calculateDataParity()
{
    if (checkSum % 2 == 0) {
        dataParityBit = 0;
    } else {
        dataParityBit = 1;
    }
    return dataParityBit;
}

int Checksum::calculateChecksumParity()
{
    int checkSum = Checksum::checkSum;
    int CheckSumCount = 0;

    for(int i = 0; i < 4; i++)
    {
        CheckSumCount += checkSum & 1;
        checkSum = checkSum >> 1;
    }

    if(CheckSumCount % 2 == 0) {
        checkSumParityBit = 0;
    } else {
        checkSumParityBit = 1;
    }

    //Checksum::CheckSumCount = CheckSumCount;
    //Checksum::checkSumParityBit = checkSumParityBit;
    return checkSumParityBit;
}

uint8_t Checksum::getlowData()
{
    std::cout << "lowout " << std::bitset<8>(lowData) << std::endl;
    return lowData;
    
}

uint8_t Checksum::gethighData()
{
    uint8_t highData = (checkSumParityBit * 128) + (dataParityBit * 64) + (checkSum * 4) + Checksum::highData;
    std::cout << "highout " << std::bitset<8>(highData) << std::endl;
    return highData;
}

int main()
{
    Checksum checksum;
    checksum.updateData();
    checksum.calculateChecksum();
    checksum.calculateDataParity();
    checksum.calculateChecksumParity();
    checksum.getlowData();
    checksum.gethighData();
    return 0;
}*/