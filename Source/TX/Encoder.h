#pragma once
#include <stdint.h>

class Encoder
{
private:

    // Low and high parts of the ADC (potentiometer).
    uint8_t lowData {};
    uint8_t highData {};

    // Variables to store checksum and parity bits.
    int checkSum {}; 
    int dataParityBit {};
    int checkSumParityBit {};

public:

    Encoder() : lowData(0) , highData(0) {} 

    // Methods to update variables and execute methods developed later on.
    void updateData(const uint8_t& lowData,const uint8_t& highData);

    // Methods to generate checksum and parity bits.
    int bitCounter(); // Method to count the number of '1' in the 10 bits of the potentiometer (data). Useful for generating checksum and parity bits.
    int dataParity(); 
    int checksumParity();

    // Methods to obtain the low part and encoded low part.
    uint8_t getlowData();
    uint8_t gethighData();

    ~Encoder() {}

};