#include "RH_ASK.h" // Radiohead library 
#include "Encoder.h"
#include "anomalyDet.h"

#define POT_INPUT A0 //declaro el pin que voy a usar para el potenciometro (analog)  

int potValue {}; // adc 10 bit (0-1023) donde esta conectado el potenciometro (fondo escala=5v)

RH_ASK module(4000); // inicializo objeto module de la clase RH_ASK con el contructor parametrizado con bitrate y se puede modificar el pin tambien
Encoder encoder;  // checksum + parity
PotAnomalyDet potAnomaly(1,100);

byte message[4];

void setup() 
{
  Serial.begin(9600); // baudrate console
  if(!module.init())
  {
    Serial.println("Initialization error!");
  }

  pinMode(2, INPUT);
  
}
int keyState = digitalRead(2);
void sendData(int potValue)
{
    encoder.updateData(lowByte(potValue),highByte(potValue));
    Serial.println(potValue);
    // creo mensaje, consta de 4 partes... byte de start... x2 byte de datos (10 bits del adc, puedo aprovechar los 6 bit que me sobran para redundancias! )
     // array of bite_word type, size 4
     // Byte de start  10101010
    message[0] = 0b10101010;
    message[1] = encoder.gethighData(); // parte alta de potvalue
    message[2] = encoder.getlowData();  // parte baja de potvalue
    message[3] = 0b01010101; // byte de stop 01010101

    byte* messagePtr = &message[0];

    //Serial.println(message[0], HEX);
   // Serial.println(message[1], BIN);
    //Serial.println(message[2], BIN);
    //Serial.println(message[3], HEX);
    
    module.send(messagePtr, sizeof(message));
  
    module.waitPacketSent();

    //delay(50); //ajustar

}

void loop() 
{
  //Serial.println(keyState);
  potValue = analogRead(POT_INPUT);
    
  if (keyState==HIGH)
     {
    potAnomaly.anomalyDet(potValue);

//usar boton reset arduino para comenzar el programa de cero si se bloquea la tx.
    if (!potAnomaly.getanomalyDet())
    {
    sendData(potValue);
    }
    else {
    Serial.println("--- ANOMALY DETECTED ---");
    Serial.println("--- ANOMALY DETECTED ---");
    Serial.println("--- ANOMALY DETECTED ---");
    Serial.println("--- ANOMALY DETECTED ---");
    while(true)
    {
      sendData(potAnomaly.getLastValue());
    }
    }
   }


   else {
    sendData(potValue);
   }
}