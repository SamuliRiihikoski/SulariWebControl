#include "Connection.h"

#define CYCLE_DURATION 10000 // ms -> 10s

long start;
const int PIN_temperature = A0;

void setup() 
{
  Serial.begin(9600);
  start = millis();
  ESP_chip Esp01; // Handle ESP-01 methods
  Esp01.connect_wifi();
}

void loop() 
{  
  ESP_chip Esp01; // Handle ESP-01 methods
  Esp01.readSerial();
  
  if (millis() - start > CYCLE_DURATION)
  {
    int value = analogRead(PIN_temperature);
    value = (value*50000) / 1023;

    Esp01.send_GET(value);
    start = millis();
  }
}
