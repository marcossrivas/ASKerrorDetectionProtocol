#include <RH_ASK.h>
#include "check_format.h"

#define PWM_PIN 7

int potValue {};//10 bit data from tx

RH_ASK module(2000); // inicializo objeto module de la clase RH_ASK con el contructor parametrizado con bitrate y se puede modificar el pin tambien
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
  byte message[4];
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
      analogWrite(PWM_PIN, map(potValue, 0, 1023, 0, 255)); 
    }
  }
  
}
