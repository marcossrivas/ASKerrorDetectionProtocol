#pragma once
#include <stdint.h>

class Decoder
{
private:

    // Raw data. Paquete de 4 bytes.
    uint8_t startByte {};
    uint8_t highData {};
    uint8_t lowData {};
    uint8_t stopByte {};

    // Aquí almaceno la información de control de errores, a la cual luego le aplico métodos de omparación.
    int checkSumData {}; 
    int dataParityBit {}; 
    int checkSumParityBit {}; 

    // Variables auxiliares.
    int dataBitCounter{}; 
    int checkSumCt{}; 
    
    // Extraigo valor del potenciómetro recibido.
    uint8_t rawLowData {};
    uint8_t rawHighData {};

public:

    Decoder() 
    {}

    //  Método para actualizar el valor de cada byte de información (Raw data variables) y ejecutar los métodos de comparación más adelante enunciados.
    void init(const uint8_t* buffer); 

    // Métodos de extracción de datos.
    void extractRawData(); // Método para extraer valor del potenciómetro.
    int bitCounter(); // Método para contar cantidad de '1' en los 10 bits del potenciómetro (data).

    int extractCheckSum(); // Método para extraer checksum de Rawdata.
    int checkSumCounter(); // Método para contar cantidad de '1' en checksum.
    
    // Métodos de control de errores.
    bool checkStart(); // Método para verificar byte de start.
    bool checkSum(); // Método para corroborar que el checksum está correcto.
    bool checkParitydata(); // Método para controlar paridad data.
    bool checkParityCheckSum(); // Métodos para controlar paridad de checksum.
    bool checkParity(); // Método para englobar los dos anteriores en un único output booleano.
    bool checkStop(); // Método para verificar byte de stop
    
    // Métodos para obtener datos del potenciómetro. 
    uint8_t getlowData();
    uint8_t gethighData();

    ~Decoder() 
    {}

};