#pragma once
#include <stdint.h>
#include <stdlib.h>

class Buffer // Circular Buffer. Creo buffer para almacenar temporalmente los valores pasados del ADC(pot)
{
protected:

    uint16_t* buffer {};
    uint16_t potData {}; // Datos de 2 bytes (potenciometro)
    const int buffer_size {}; 
    bool bufferStatus {}; // true Full // false Not full 

private:

    // Variables auxiliares.
    int bufferSizeCount {};
    int position {};

public:

    Buffer(int buffer_size) : buffer_size(buffer_size)
    {
        buffer = new uint16_t[buffer_size]; // Creo buffer segun el tamaño inicializado

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

    void fillBuffer(); // Metodo para llenar buffer
    void checkBufferStatus(); // Metodo para controlar estado del buffer mediante variable bufferStatus.
    void updateBuffer(); // Metodo para actualizar buffer. (desplazamiento y escritura).

    uint16_t getLastValue();// Metodo para obtener ultimo valor guardado en el buffer.

    virtual ~Buffer()
    {
        delete[] buffer; 
    }
};


class PotAnomalyDet : public Buffer // Deteccion de anomalias (Clase orientada a realizar procesos de valor actual con pasados almacenados en el buffer)
{   
private:

    const int threshold {}; 
    bool wrongData {};

public:

    PotAnomalyDet(int buffer_size,int threshold) : Buffer(buffer_size) , threshold(threshold) {}

    void processPotData(); // Metodo para comparar valor actual leido con valores guardados en el buffer
    void anomalyDet(const uint16_t& potData); // Metodo para comparar valor actual con pasados. Usa variable umbral.
    bool getanomalyDet(); // Metodo para obtener valor booleano si se detecto anomalia.
 
    ~PotAnomalyDet() {}

};