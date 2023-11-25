#pragma once
#include <stdint.h>
#include <stdlib.h>

class Buffer // Creo buffer (circular) para almacenar temporalmente los valores pasados del ADC(pot).
{
protected:

    uint16_t* buffer {};
    uint16_t potData {}; // Datos de 2 bytes (potenciómetro)
    const int buffer_size {}; 
    bool bufferStatus {}; // true -> Full // false -> Not full 

private:

    // Variables auxiliares.
    int bufferSizeCount {};
    int position {};

public:

    Buffer(int buffer_size);
    
    void fillBuffer(); // Método para llenar buffer
    void checkBufferStatus(); // Método para controlar estado del buffer mediante variable bufferStatus.
    void updateBuffer(); // Método para actualizar buffer. (desplazamiento y escritura).

    uint16_t getLastValue();// Método para obtener último valor guardado en el buffer.

    ~Buffer();

};

// Detección de anomalías: Clase orientada a realizar procesos de comparación ..
// .. de valor actual con pasados (almacenados en el buffer)

class PotAnomalyDet : public Buffer 
{   
private:

    const int threshold {}; 
    bool wrongData {};

public:

    PotAnomalyDet(int buffer_size,int threshold) : Buffer(buffer_size) , threshold(threshold) 
    {}

    void processPotData(); // Método para comparar valor actual leido con valores guardados en el buffer.
    void anomalyDet(const uint16_t& potData); // Método para comparar valor actual con pasados. Usa variable umbral.
    bool getanomalyDet(); // Método para obtener valor booleano si se detectó anomalía.
 
    ~PotAnomalyDet() 
    {}

};