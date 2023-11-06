#include "RH_ASK.h" // Header de la libreria RadioHead para utilizar modulo ASK. Reference: https://www.airspayce.com/mikem/arduino/RadioHead/index.html
#include "Encoder.h"
#include "anomalyDet.h"

#define POT_INPUT A0 // Declaro el pin que voy a usar para el potenciometro (analog input).


//-- Codigo de deteccion de anomalias en lectura de potValue --// 

// ACTIVAR -> PIN 2 digital a Vcc /// DESACTIVAR -> PIN 2 digital a Gnd.
#define ENABLE_ANOMALY_DET_PIN 2 // Declaro pin que voy a usar para activar deteccion de anomalias en el potenciometro.
//FUNCIONAMIENTO -> Se compara valor actual con anteriores(BUFFER_SIZE) segun un umbral (THRESHOLD).
#define ANOMALY_DET_BUFFER_SIZE 1 // Declaro el tamaño del buffer que voy a usar para deteccion de anomalias. En este caso solo comparo con valor pasado
#define ANOMALY_DET_THRESHOLD 100 // Declaro el umbral para que un dato sea detectado como anomalia.

//---//

RH_ASK module(4000); // Inicializo objeto module de la clase RH_ASK con el constructor parametrizado con bit rate.
Encoder encoder;  // Checksum + Paridad.
PotAnomalyDet potAnomaly(ANOMALY_DET_BUFFER_SIZE, ANOMALY_DET_THRESHOLD); // Deteccion de anomalias

int potValue {}; // ADC 10 bit (0-1023) donde esta conectado el potenciometro (fondo escala = 5v).

// Espacio en memoria para almacenar mensajes recibidos
byte message[4];
byte* messagePtr = &message[0];

// -- ARDUINO -- SETUP -- //

void setup() 
{
  Serial.begin(9600); // Set Baudrate transmision serial.
  if(!module.init())
  {
    Serial.println("Initialization error!");
  }
  pinMode(ENABLE_ANOMALY_DET_PIN, INPUT);
}


int ENABLE_ANOMALY_DET = digitalRead(ENABLE_ANOMALY_DET_PIN); // lectura del pin para activar deteccion de anomalias en el potenciometro.

void sendData(int potValue) //Metodo para enviar informacion.
{
  encoder.updateData(lowByte(potValue),highByte(potValue));

  message[0] = 0b10101010; // byte de start 0x55
  message[1] = encoder.gethighData(); // parte alta de potValue.
  message[2] = encoder.getlowData();  // parte baja de potValue.
  message[3] = 0b01010101; // byte de stop 0xAA

  module.send(messagePtr, sizeof(message));// Metodo para enviar mensaje.

  module.waitPacketSent();// Espera que se envie.
}


// -- ARDUINO -- LOOP -- //

void loop() 
{
  potValue = analogRead(POT_INPUT); //lee valor del potenciometro.
    
  if (ENABLE_ANOMALY_DET==HIGH)
  {
    potAnomaly.anomalyDet(potValue); //Deteccion anomalias.
    
    if (!potAnomaly.getanomalyDet()) 
    {
      // NO detecto anomalia.
      sendData(potValue); //Funcion implementada arriba.
    }
    else
    {
      // SI detecto anomalia. Se queda en valor anterior guardado en el buffer. Se debe resetar Arduino.
      Serial.println("--- ANOMALY DETECTED ---"); 
      while(true) 
      {
        sendData(potAnomaly.getLastValue());
      }
    }
  }
  else // ENABLE_ANOMALY_DET==LOW
  {
    sendData(potValue); //Funcion implementada arriba.
  }
}