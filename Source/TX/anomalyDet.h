#include <stdint.h>
#include <stdlib.h>

//-- proyecto: control riguroso de consistencia de datos enviados por un potenciometro atravez de un transmisor 433mhz OOK. 
//-- orientado a aplicaciones que no se necesitan altas velocidades de transmision de datos y admiten una minima latencia(depende del hardware)
// -- control pot value noises en tx
// -- heavy error detection entre tx-rx. no hay correccion solo deteccion
//usar ifdef para anomaly detections

class PotAnomalyDet 
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

    PotAnomalyDet(int buffer_size,int threshold) : buffer_size(buffer_size) , threshold(threshold)
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

    void anomalyDet(const uint16_t& potData);

    bool getanomalyDet();
    uint16_t getLastValue();
    
    ~PotAnomalyDet()
    {
        delete[] buffer;
    }
    
};