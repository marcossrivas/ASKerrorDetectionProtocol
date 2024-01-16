#include "anomalyDet.h"

// Purpose of each method declared in the header.

// Creating a buffer based on the initialized size.
Buffer::Buffer(int buffer_size) : buffer_size(buffer_size)
{
    buffer = new uint16_t[buffer_size]; 

    bufferStatus = false;
    
    //Init variables aux.
    bufferSizeCount = 0;
    position = buffer_size - 1;

    //Init buffer
    for (int i = 0; i < buffer_size; i++)
    {
        buffer[i] = 0;
    }
}

void Buffer::fillBuffer()
{
    buffer[position] = potData;
    position -= 1;
    bufferSizeCount += 1;
}

void Buffer::checkBufferStatus()
{
    if (bufferSizeCount == buffer_size)
    {
        bufferStatus = true;
    }
}

void PotAnomalyDet::processPotData() // Method to detect if the read value exceeds the threshold set with the values stored in the buffer.
{
    for (int i = 0; i < buffer_size; i++)
    {
        if((abs(potData - buffer[i])) > threshold)
        {
            wrongData = true;
            break;
        }
    }
}

void Buffer::updateBuffer()
{
    for (int i = 0; i < buffer_size; i++)
    {
        buffer[(buffer_size - 1) - i] = buffer[(buffer_size - 2) - i];
    }
    buffer[0] = potData;
}


/// --  Process block -- ///

void PotAnomalyDet::anomalyDet(const uint16_t& potData) 
{
    this->potData = potData;
    wrongData = false;

    checkBufferStatus();

    if(bufferStatus==false)
    {
        fillBuffer();   
    }
    else
    {
        processPotData();
        if(wrongData == false)
        {
            updateBuffer();
        }
    }
}

/// --- ///

uint16_t Buffer::getLastValue()
{
  return buffer[0];
}

bool PotAnomalyDet::getanomalyDet()
{
    return wrongData;
}

Buffer::~Buffer()
{
    delete[] buffer; 
}


