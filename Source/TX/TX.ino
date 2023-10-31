#include "RH_ASK.h" // Radiohead library 

#include "error_correction.h"

#define POT_INPUT A0 //declaro el pin que voy a usar para el potenciometro (analog)
using byte_word = unsigned char; // voy a usar palabras de 1 byte  

int potValue {}; // adc 10 bit (0-1023) donde esta conectado el potenciometro (fondo escala=5v)

RH_ASK Module(2000); // inicializo objeto Module de la clase RH_ASK con el contructor parametrizado con bitrate y se puede modificar el pin tambien
 
void setup() 
{
  Serial.begin(9600); // baudrate console
  if(!Module.init())
  {
    Serial.println("initialization error");
  }
}

void loop() 
{
    potValue = analogRead(POT_INPUT);
     
    // creo mensaje, consta de 4 partes... byte de start... x2 byte de datos (10 bits del adc, puedo aprovechar los 6 bit que me sobran para redundancias! )
    byte_word message[4]; // array of bite_word type, size 4
    message[0] = 0xAA; // Byte de start  10101010
    message[1] = highByte(potValue); // parte alta de potvalue
    message[2] = lowByte(potValue);  // parte baja de potvalue
    message[3] = 0x55; // byte de stop 01010101

    byte_word* messagePtr = &message[0];
    
    Module.send(messagePtr, sizeof(message));

    Module.waitPacketSent();

    delay(150); //ajustar
}
