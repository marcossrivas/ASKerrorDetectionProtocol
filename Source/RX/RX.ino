#include <RH_ASK.h>
#include "check_format.h"

#define PWM_PIN 6

int potValue {};//10 bit data from tx

RH_ASK module(4000); // inicializo objeto module de la clase RH_ASK con el contructor parametrizado con bitrate y se puede modificar el pin tambien
CheckFormat format; //checkeo start-stop ; paridad y checksum ; extraigo data

void setup() 
{
  Serial.begin(9600); // baudrate console
  if(!module.init())
  {
    Serial.println("Initialization error!");
  }
  pinMode(PWM_PIN, OUTPUT);
}

void loop() 
{ 
  byte message[4]; // demo message..
    //message[0] = 0b10101010; // Byte de start  10101010
   // message[1] = 0b10010011; // parte alta de potvalue
   // message[2] = 0b11110011;  // parte baja de potvalue
   // message[3] = 0b01010101; // byte de stop 01010101

  byte* buffer = &message[0];
  byte messageLenght = sizeof(message);

  format.initFormat(buffer);

  if (module.recv(buffer,&messageLenght))
  {
    if (format.checkStart() && format.checkParity() && format.checkSum() && format.checkStop())
   {
      byte highData = format.gethighData();
      byte lowData = format.getlowData();
      potValue = word(highData, lowData);
      Serial.println(potValue);
  
      analogWrite(PWM_PIN, map(potValue, 0, 1023, 0, 255)); 
      
    }
  }
  else{//keep the last value
  }
}
