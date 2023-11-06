#pragma once
#include <stdint.h>

class Decoder
{
private:

    // Rawdata. Paquete de 4 bytes.
    uint8_t startByte {};
    uint8_t highData {};
    uint8_t lowData {};
    uint8_t stopByte {};

    // Aqui almaceno la informacion de control de errores, a la cual luego le aplico metodos de comparacion.
    int checkSumData {}; 
    int dataParityBit {}; 
    int checkSumParityBit {}; 

    // Variables auxiliares.
    int dataBitCounter{}; 
    int checkSumCt{}; 
    
    // Extraigo valor del potenciometro recibido.
    uint8_t rawLowData {};
    uint8_t rawHighData {};

public:

    Decoder() {}

    // Metodo para actualizar el valor de cada byte de informacion (Rawdata variables) y ejecutar los metodos de comparacion mas adelante enunciados.
    void init(const uint8_t* buffer); 

    // Metodos de extraccion de datos.
    void extractRawData(); // Metodo para extraer valor del potenciometro.
    int bitCounter(); // Metodo para contar cantidad de '1' en los 10 bits del potenciometro (data).

    int extractCheckSum(); // Metodo para extraer checksum de Rawdata.
    int checkSumCounter(); // Metodo para contar cantidad de '1' en checksum.
    
    // Metodos de control de errores.
    bool checkStart(); // Metodo para verificar byte de start.
    bool checkSum(); // Metodo para corroborar que el checksum esta correcto.
    bool checkParitydata(); // Metodo para controlar paridad data.
    bool checkParityCheckSum(); // Metodos para controlar paridad de checksum.
    bool checkParity(); // Metodo para englobar los dos anteriores en un unico output booleano.
    bool checkStop(); // Metodo para verificar byte de stop
    
    //Metodos para obtener datos del potenciometro. 
    uint8_t getlowData();
    uint8_t gethighData();

    ~Decoder() {}

};