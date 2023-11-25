#include <RH_ASK.h> // Header de la librería RadioHead para utilizar modulo ASK. Reference: https://www.airspayce.com/mikem/arduino/RadioHead/index.html
#include "Decoder.h"

#define PWM_PIN 6 // Defino PIN 6 de Arduino para salida PWM led.

RH_ASK module(2500); // Inicializo objeto module de la clase RH_ASK con el constructor parametrizado con bit rate. Pin data (default) -> 11
Decoder decoder; // Incializo objeto de clase Decoder. Ver Decoder.h para más info.

int potValue {0}; // Valor del ADC (potenciómetro) recibido. 10 bits

// Espacio en memoria para almacenar mensajes recibidos
byte message[4];
byte* buffer = &message[0];
byte messageLenght = sizeof(message);


// -- SETUP -- //

void setup() 
{
  Serial.begin(9600); // Set Baudrate transmisión serial.
  if(!module.init()) 
  {
    Serial.println("Initialization error!");
  }

  pinMode(PWM_PIN, OUTPUT);
}

// -- LOOP -- //

void loop() 
{ 
  decoder.init(buffer); // Ver método init en Decoder para más info.

  if (module.recv(buffer,&messageLenght)) // Comprueba que reciba datos y los guarda en buffer.
  {
    if (decoder.checkStart() && decoder.checkParity() && decoder.checkSum() && decoder.checkStop()) // Condicionales para declarar mensaje válido.
   {
      byte highData = decoder.gethighData(); // Obtengo parte alta de potenciómetro.
      byte lowData = decoder.getlowData(); // Obtengo parte baja de potenciómetro.
      potValue = word(highData, lowData);// Unifico los dos bytes anteriores en una palabra de 2 bytes.
      
      analogWrite(PWM_PIN, map(potValue, 0, 1023, 0, 255)); // Mapeo los valores recibidos del potenciómetro (de 0 a 1023) de 0 a 255 para PWM. 
    }
  }
  else
  {
    analogWrite(PWM_PIN, map(potValue, 0, 1023, 0, 255)); //Si se corta la transmisión, mantengo el led en ese estado.
  }
}
