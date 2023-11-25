#include "anomalyDet.h"

// Propósito de cada método anunciado en header.

// Creo buffer según el tamaño inicializado
Buffer::Buffer(int buffer_size) : buffer_size(buffer_size)
{
    buffer = new uint16_t[buffer_size]; 

    bufferStatus = false;
    
    //Init variables aux.
    bufferSizeCount = 0;
    position = buffer_size - 1;

    //Inicializo buffer
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

void PotAnomalyDet::processPotData() // Método para detectar si el valor leído supera el umbral establecido con los valores guardados en el buffer.
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


