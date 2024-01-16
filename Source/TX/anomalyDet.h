#pragma once
#include <stdint.h>
#include <stdlib.h>

class Buffer // Creating a circular buffer to temporarily store past values from the ADC (pot).
{
protected:

    uint16_t* buffer {};
    uint16_t potData {}; // 2-byte data (potentiometer)
    const int buffer_size {}; 
    bool bufferStatus {}; // true -> Full // false -> Not full 

private:

    // Aux. variables
    int bufferSizeCount {};
    int position {};

public:

    Buffer(int buffer_size);
    
    void fillBuffer(); // Method to fill the buffer.
    void checkBufferStatus(); // Method to control the state of the buffer using the bufferStatus variable.
    void updateBuffer(); // // Method to update the buffer (shift and write).

    uint16_t getLastValue();// Method to retrieve the last value stored in the buffer.

    ~Buffer();

};

// Anomaly Detection: Class designed to perform comparison processes of the current value with past values (stored in the buffer).

class PotAnomalyDet : public Buffer 
{   
private:

    const int threshold {}; 
    bool wrongData {};

public:

    PotAnomalyDet(int buffer_size,int threshold) : Buffer(buffer_size) , threshold(threshold) 
    {}

    void processPotData(); // Method to compare the currently read value with values stored in the buffer.
    void anomalyDet(const uint16_t& potData); // Method to compare the current value with past values. Uses a threshold variable.
    bool getanomalyDet(); // Method to obtain a boolean value indicating whether an anomaly was detected.
 
    ~PotAnomalyDet() 
    {}

};