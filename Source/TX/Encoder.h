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

    // Metodos para actualizar variables y ejecutar metodos desarrollados mas adelante.
    void updateData(const uint8_t& lowData,const uint8_t& highData);

    // Metodos para generar chechsum y bits de paridad
    int bitCounter();
    int dataParity();
    int checksumParity();

    // Metodos para obtener parte baja y parte baja codificada.
    uint8_t getlowData();
    uint8_t gethighData();

    ~Encoder() {}

};