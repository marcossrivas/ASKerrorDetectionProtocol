#include "RH_ASK.h" // Header de la librería RadioHead para utilizar modulo ASK. Reference: https://www.airspayce.com/mikem/arduino/RadioHead/index.html
#include "Encoder.h"
#include "anomalyDet.h"

#define POT_INPUT A0 // Declaro el pin que voy a usar para el potenciómetro (analog input).


//-- Código de detección de anomalías en lectura de potValue (puede ser desactivado) --// 

// ACTIVAR -> PIN 2 digital a Vcc /// DESACTIVAR -> PIN 2 digital a Gnd.
#define ENABLE_ANOMALY_DET_PIN 2 // Declaro pin que voy a usar para activar deteccion de anomalias en el potenciómetro.
//FUNCIONAMIENTO -> Se compara valor actual con anteriores(BUFFER_SIZE) según un umbral (THRESHOLD).
#define ANOMALY_DET_BUFFER_SIZE 1 // Declaro el tamaño del buffer que voy a usar para deteccion de anomalias. En este caso solo comparo con valor pasado.
#define ANOMALY_DET_THRESHOLD 100 // Declaro el umbral para que un dato sea detectado como anomalía.

//---//

RH_ASK module(2500); // Inicializo objeto module de la clase RH_ASK con el constructor parametrizado con bit rate. Pin de datos(default) -> 12 
Encoder encoder;  // Checksum + Paridad.
PotAnomalyDet potAnomaly(ANOMALY_DET_BUFFER_SIZE, ANOMALY_DET_THRESHOLD); // Detección de anomalías.

int potValue {}; // ADC 10 bit (0-1023) donde esta conectado el potenciómetro (fondo escala = 5v).

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


int ENABLE_ANOMALY_DET = digitalRead(ENABLE_ANOMALY_DET_PIN); // Lectura del pin para activar detección de anomalías en el potenciómetro.

void sendData(int potValue) //Método para enviar información.
{
  encoder.updateData(lowByte(potValue),highByte(potValue));

  message[0] = 0b10101010; // byte de start 0x55
  message[1] = encoder.gethighData(); // parte alta de potValue.
  message[2] = encoder.getlowData();  // parte baja de potValue.
  message[3] = 0b01010101; // byte de stop 0xAA

  module.send(messagePtr, sizeof(message));// Método para enviar mensaje.

  module.waitPacketSent();// Espera que se envíe.
}


// -- ARDUINO -- LOOP -- //

void loop() 
{
  potValue = analogRead(POT_INPUT); //Lee valor del potenciómetro.
    
  if (ENABLE_ANOMALY_DET==HIGH)
  {
    potAnomaly.anomalyDet(potValue); //Detección anomalías.
    
    if (!potAnomaly.getanomalyDet()) 
    {
      // NO detectó anomalía.
      sendData(potValue); //Función implementada arriba.
    }
    else
    {
      // SI detectó anomalía. Se queda en valor anterior guardado en el buffer. Se debe resetar Arduino.
      Serial.println("--- ANOMALY DETECTED ---"); 
      while(true) 
      {
        sendData(potAnomaly.getLastValue());
      }
    }
  }
  else // ENABLE_ANOMALY_DET==LOW
  {
    sendData(potValue); //Función implementada arriba.
  }
}