#include <RH_ASK.h> // Header of the RadioHead library for using the ASK module. Reference: https://www.airspayce.com/mikem/arduino/RadioHead/index.html
#include "Decoder.h"

#define PWM_PIN 6 // Defining PIN 6 of Arduino for PWM output to the LED.

RH_ASK module(2500); // Initializing the module object of the RH_ASK class with the parameterized constructor using the bit rate. Default data pin -> 11.
Decoder decoder; // Initializing an object of the Decoder class. Refer to Decoder.h for more information.

int potValue {0}; // Value of the received ADC (potentiometer). 10 bits.

// Memory space to store received messages.
byte message[4];
byte* buffer = &message[0];
byte messageLenght = sizeof(message);


// -- SETUP -- //

void setup() 
{
  Serial.begin(9600); // Set Baudrate Serial transmission.
  if(!module.init()) 
  {
    Serial.println("Initialization error!");
  }

  pinMode(PWM_PIN, OUTPUT);
}

// -- LOOP -- //

void loop() 
{ 
  decoder.init(buffer); // Refer to the init method in Decoder for more information.

  if (module.recv(buffer,&messageLenght)) // Checks for data reception and saves it in the buffer.
  {
    if (decoder.checkStart() && decoder.checkParity() && decoder.checkSum() && decoder.checkStop()) // Conditionals to declare a valid message.
   {
      byte highData = decoder.gethighData(); // Obtaining the high part of the potentiometer.
      byte lowData = decoder.getlowData(); // Obtaining the low part of the potentiometer.
      potValue = word(highData, lowData);// Combining the previous two bytes into a 2-byte word.
      
      analogWrite(PWM_PIN, map(potValue, 0, 1023, 0, 255)); // Mapping the received values from the potentiometer (0 to 1023) to the range of 0 to 255 for PWM.
    }
  }
  else
  {
    analogWrite(PWM_PIN, map(potValue, 0, 1023, 0, 255)); // If the transmission is stop, I maintain the LED in that state.
  }
}
