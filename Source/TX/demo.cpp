/*#include <iostream>
#include <stdint.h>
#include <bitset>
#include <cmath>

//-- proyecto: control riguroso de consistencia de datos enviados por un potenciometro atravez de un transmisor 433mhz OOK. 
//-- orientado a aplicaciones que no se necesitan altas velocidades de transmision de datos y admiten una minima latencia(depende del hardware)
// -- control pot value noises en tx
// -- heavy error detection entre tx-rx. no hay correccion solo deteccion
//usar ifdef para anomaly detections

class PotDenoise 
{   
private:

    uint16_t potData {};
    uint16_t* buffer {};

    const int buffer_size {};
    const int threshold {};

    int bufferSizeCount {};
    bool boolFillBuffer {};
    int position {};

    bool wrongData {};

public:

    PotDenoise(int buffer_size,int threshold) : buffer_size(buffer_size) , threshold(threshold)
    {
        buffer = new uint16_t[buffer_size]; //size 4 words of 2 bytes... test

        boolFillBuffer = false;
        
        bufferSizeCount = 0;
        position = buffer_size - 1;

        //init buffer
        for (int i = 0; i < buffer_size; i++)
        {
            buffer[i] = 0;
        }
    }

    void checkBufferStatus();

    void fillBuffer();
    void processPotData();
    void updateBuffer();

    void anomalyDet(uint16_t potData);

    bool getanomalyDet();
//testinggg
    void printbuffer();
    
    ~PotDenoise()
    {
        delete[] buffer;
    }

};

void PotDenoise::fillBuffer()
{
    std::cout << "fill buffer on" << std::endl;

    buffer[position] = potData;
    position -= 1;
    bufferSizeCount += 1;
}

void PotDenoise::checkBufferStatus()
{
    if (bufferSizeCount == buffer_size)
    {
        boolFillBuffer = true;
    }
}

void PotDenoise::processPotData()
{
    for (int i = 0; i < buffer_size; i++)
    {
        if((abs(potData - buffer[i])) > threshold)
        {
            std::cout << "error detected" <<std::endl;
            wrongData = true;
            break;
        }
    }
}

void PotDenoise::updateBuffer()
{
    std::cout << "updating buffer" << std::endl;
    for (int i = 0; i < buffer_size; i++)
    {
        buffer[(buffer_size - 1) - i] = buffer[(buffer_size - 2) - i];
    }
    buffer[0] = potData;
}

void PotDenoise::anomalyDet(uint16_t potData)
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

bool PotDenoise::getanomalyDet()
{
    return wrongData;
}

void PotDenoise::printbuffer()
{
    for (int i = 0; i < buffer_size; i++)
    {
        std::cout << buffer[i] << std::endl;
    }
}


//TESTINGGG


int main()
{
    int dataDemochain[8] = {256,257,265,278,500,501,506,509};
    PotDenoise obj(3,50);
    for (int i = 0; i < 8; i++)
    {
        obj.anomalyDet(dataDemochain[i]);
        obj.printbuffer();
    }

    return 0;
}
*/