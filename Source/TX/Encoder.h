#pragma once
#include <stdint.h>

class Encoder
{
private:

    // Parte baja y alta del ADC (potenciometro).
    uint8_t lowData {};
    uint8_t highData {};

    // Variables para guardar checksum y bits de paridad.
    int checkSum {}; 
    int dataParityBit {};
    int checkSumParityBit {};

public:

    Encoder() : lowData(0) , highData(0) {} 

    // Métodos para actualizar variables y ejecutar metodos desarrollados mas adelante.
    void updateData(const uint8_t& lowData,const uint8_t& highData);

    // Métodos para generar chechsum y bits de paridad
    int bitCounter(); // Método para contar cantidad de '1' en los 10 bits del potenciómetro (data). Útil para generar checksum y bits de paridad.
    int dataParity(); 
    int checksumParity();

    // Métodos para obtener parte baja y parte baja codificada.
    uint8_t getlowData();
    uint8_t gethighData();

    ~Encoder() {}

};