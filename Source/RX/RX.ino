#include <RH_ASK.h> // Header de la libreria RadioHead para utilizar modulo ASK. Reference: https://www.airspayce.com/mikem/arduino/RadioHead/index.html
#include "Decoder.h"

#define PWM_PIN 6 // Defino PIN 6 de Arduino para salida PWM led.

RH_ASK module(4000); // Inicializo objeto module de la clase RH_ASK con el constructor parametrizado con bit rate.
Decoder decoder; // Incializo objeto de clase Decoder. Ver Decoder.h para mas info.

int potValue {0}; // Valor del ADC (potenciometro) recibido. 10 bits

// Espacio en memoria para almacenar mensajes recibidos
byte message[4];
byte* buffer = &message[0];
byte messageLenght = sizeof(message);


// -- SETUP -- //

void setup() 
{
  Serial.begin(9600); // Set Baudrate transmision serial.
  if(!module.init()) 
  {
    Serial.println("Initialization error!");
  }

  pinMode(PWM_PIN, OUTPUT);
}

// -- LOOP -- //

void loop() 
{ 
  decoder.init(buffer); // Ver metodo init en Decoder para mas info.

  if (module.recv(buffer,&messageLenght)) // Compruba que reciba datos y los guarda en buffer antes inicializado.
  {
    if (decoder.checkStart() && decoder.checkParity() && decoder.checkSum() && decoder.checkStop()) // Condionales para declarar mensaje valido.
   {
      byte highData = decoder.gethighData(); // Obtengo parte alta de potenciometro.
      byte lowData = decoder.getlowData(); // Obtengo parte baja de potenciometro.
      potValue = word(highData, lowData);// Unifico los dos bytes anteriores en una palabra de 2 bytes.
      
      analogWrite(PWM_PIN, map(potValue, 0, 1023, 0, 255)); // Mapeo los valores recibidos del potenciometro (de 0 a 1023) de 0 a 255 para PWM. 
    }
  }
  else
  {
    analogWrite(PWM_PIN, map(potValue, 0, 1023, 0, 255)); //Si se corta la transmision, mantengo el led en ese estado.
  }
}
