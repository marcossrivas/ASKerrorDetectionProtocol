#pragma once
#include <stdint.h>

class Decoder
{
private:

    // Raw data. 4 bytes Packet.
    uint8_t startByte {};
    uint8_t highData {};
    uint8_t lowData {};
    uint8_t stopByte {};

    // Here, I store the error control information, to which I later apply comparison methods.
    int checkSumData {}; 
    int dataParityBit {}; 
    int checkSumParityBit {}; 

    // Aux. Variables.
    int dataBitCounter{}; 
    int checkSumCt{}; 
    
    // Extracting the received potentiometer value.
    uint8_t rawLowData {};
    uint8_t rawHighData {};

public:

    Decoder() 
    {}

    // Method to update the value of each byte of information (Raw data variables) and execute the comparison methods later stated.
    void init(const uint8_t* buffer); 

    // Data extraction methods.
    void extractRawData(); // Method to extract the potentiometer value.
    int bitCounter(); // Method to count the number of '1' in the 10 bits of the potentiometer (data).

    int extractCheckSum(); // Method to extract the checksum from Rawdata.
    int checkSumCounter(); // Method to count the number of '1' in the checksum.
    
    // Error control methods.
    bool checkStart(); // Method to verify the start byte.
    bool checkSum(); // Method to confirm that the checksum is correct.
    bool checkParitydata(); // Method to control data parity.
    bool checkParityCheckSum(); // Methods to control checksum parity.
    bool checkParity(); // Method to encapsulate the two previous ones into a single boolean output.
    bool checkStop(); // Method to verify the stop byte.
    
    // Method to obtain potentiometer data.
    uint8_t getlowData();
    uint8_t gethighData();

    ~Decoder() 
    {}

};