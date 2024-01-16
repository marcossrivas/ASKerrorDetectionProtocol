#include "RH_ASK.h" // Header of the RadioHead library for using the ASK module. Reference: https://www.airspayce.com/mikem/arduino/RadioHead/index.html
#include "Encoder.h"
#include "anomalyDet.h"

#define POT_INPUT A0 // Declaring the pin I will use for the potentiometer (analog input).

//-- Code for anomaly detection in potValue reading (can be deactivated) --//

// ENABLE -> Digital PIN 2 to Vcc /// DISABLE -> Digital PIN 2 to Gnd.
#define ENABLE_ANOMALY_DET_PIN 2 // Declaring the pin I will use to activate anomaly detection in the potentiometer.
// OPERATION -> Compares the current value with previous ones (BUFFER_SIZE) based on a threshold (THRESHOLD).
#define ANOMALY_DET_BUFFER_SIZE 1 // Declaring the size of the buffer I will use for anomaly detection. In this case, only comparing with the previous value.
#define ANOMALY_DET_THRESHOLD 100 // Declaring the threshold for a data to be detected as an anomaly.

//---//

RH_ASK module(2500); // Initializing the module object of the RH_ASK class with the parameterized constructor using the bit rate. Default data pin -> 12.
Encoder encoder;  // Checksum + Parity.
PotAnomalyDet potAnomaly(ANOMALY_DET_BUFFER_SIZE, ANOMALY_DET_THRESHOLD); // Anomaly Detection.

int potValue {}; // 10-bit ADC (0-1023) where the potentiometer is connected (full scale = 5V).

// Memory space to store received messages.
byte message[4];
byte* messagePtr = &message[0];

// -- ARDUINO -- SETUP -- //

void setup() 
{
  Serial.begin(9600); // Set Baudrate serial transmission.
  if(!module.init())
  {
    Serial.println("Initialization error!");
  }
  pinMode(ENABLE_ANOMALY_DET_PIN, INPUT);
}


int ENABLE_ANOMALY_DET = digitalRead(ENABLE_ANOMALY_DET_PIN); // Reading the pin to activate anomaly detection in the potentiometer.

void sendData(int potValue) //Method to send the information.
{
  encoder.updateData(lowByte(potValue),highByte(potValue));

  message[0] = 0b10101010; // start byte 0xAA
  message[1] = encoder.gethighData(); // potValue high part.
  message[2] = encoder.getlowData();  // potValue low part.
  message[3] = 0b01010101; // stop byte 0x55

  module.send(messagePtr, sizeof(message));// Method to send the message.

  module.waitPacketSent();// Waits for it to be sent.
}


// -- ARDUINO -- LOOP -- //

void loop() 
{
  potValue = analogRead(POT_INPUT); //Read pot value.
    
  if (ENABLE_ANOMALY_DET==HIGH)
  {
    potAnomaly.anomalyDet(potValue); //Anomaly Detection.
    
    if (!potAnomaly.getanomalyDet()) 
    {
      // NO anomaly detected.
      sendData(potValue); // Function implemented above.
    }
    else
    {
      // YES, anomaly detected. Stays at the previously stored value in the buffer. Arduino needs to be reset.
      Serial.println("--- ANOMALY DETECTED ---"); 
      while(true) 
      {
        sendData(potAnomaly.getLastValue());
      }
    }
  }
  else // ENABLE_ANOMALY_DET==LOW
  {
    sendData(potValue); // Function implemented above.
  }
}