#include "anomalyDet.h"

void PotAnomalyDet::fillBuffer()
{
    buffer[position] = potData;
    position -= 1;
    bufferSizeCount += 1;
}

void PotAnomalyDet::checkBufferStatus()
{
    if (bufferSizeCount == buffer_size)
    {
        boolFillBuffer = true;
    }
}

void PotAnomalyDet::processPotData()
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

void PotAnomalyDet::updateBuffer()
{
    for (int i = 0; i < buffer_size; i++)
    {
        buffer[(buffer_size - 1) - i] = buffer[(buffer_size - 2) - i];
    }
    buffer[0] = potData;
}

void PotAnomalyDet::anomalyDet(const uint16_t& potData)
{
    this->potData = potData;
    wrongData = false;

    checkBufferStatus();

    if(boolFillBuffer==false)
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

uint16_t PotAnomalyDet::getLastValue()
{
  return buffer[0];
}

bool PotAnomalyDet::getanomalyDet()
{
    return wrongData;
}


