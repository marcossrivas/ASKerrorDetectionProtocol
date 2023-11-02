#pragma once
#include <stdint.h>

class CheckFormat
{
private:

    uint8_t startByte {};
    uint8_t highData {};
    uint8_t lowData {};
    uint8_t stopByte {};

    int checkSumData {}; //4 bit data
    int dataParityBit {}; //1 bit data
    int checkSumParityBit {}; //1 bit data

    int dataBitCounter{}; 
    int checkSumCt{}; 
    
    uint8_t rawLowData {};
    uint8_t rawHighData {};

public:

    CheckFormat() {}

    void initFormat(const uint8_t* buffer);
    void extractRawData();

    int bitCounter();
    int checkSumCounter();
    int getCheckSum();

    bool checkSum();
    bool checkParitydata();
    bool checkParityCheckSum();
    bool checkParity();
    bool checkStop();
    bool checkStart();

    uint8_t getlowData();
    uint8_t gethighData();

    ~CheckFormat() {}
};