#include "RH_ASK.h" // Radiohead library 

#include "error_correction.h"

#define POT_INPUT A0 //declaro el pin que voy a usar para el potenciometro (analog)  

int potValue {}; // adc 10 bit (0-1023) donde esta conectado el potenciometro (fondo escala=5v)

RH_ASK module(2000); // inicializo objeto module de la clase RH_ASK con el contructor parametrizado con bitrate y se puede modificar el pin tambien
Checksum checksum;

void setup() 
{
  Serial.begin(9600); // baudrate console
  if(!module.init())
  {
    Serial.println("Initialization error!");
  }
}

void loop() 
{
    potValue = analogRead(POT_INPUT);
    checksum.updateData(lowByte(potValue),highByte(potValue));

    //Serial.println("---------");
    //Serial.println("----LOW-----");
    //Serial.println(lowByte(potValue), BIN);
    //Serial.println(checksum.getlowData(), BIN);
   // Serial.println("-----HIGH------");
   // Serial.println(highByte(potValue), BIN);
    //Serial.println(checksum.gethighData(), BIN);
    //Serial.println("---------");

    // creo mensaje, consta de 4 partes... byte de start... x2 byte de datos (10 bits del adc, puedo aprovechar los 6 bit que me sobran para redundancias! )
    byte message[4]; // array of bite_word type, size 4
    message[0] = 0b10101010; // Byte de start  10101010
    message[1] = checksum.gethighData(); // parte alta de potvalue
    message[2] = checksum.getlowData();  // parte baja de potvalue
    message[3] = 0b01010101; // byte de stop 01010101

    byte* messagePtr = &message[0];
    Serial.println(message[0], BIN);
    Serial.println(message[1], BIN);
    Serial.println(message[2], BIN);
    Serial.println(message[3], BIN);
    module.send(messagePtr, sizeof(message));

    module.waitPacketSent();

    delay(12000); //ajustar 
}
