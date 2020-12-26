#include "Connection.h"

#define UPDATE_TIME 10000 // ms -> 10s
long start;

ESP_chip Esp01; // Handle ESP-01 methods

const int tempPin = A0;
int val = 0;
float tempAmount = 0;

struct Tieto {
  int luku;
};

void setup() 
{
  Serial.begin(9600);
  start = millis();
  
  Esp01.connect_wifi();
}

void loop() 
{
  
  val = analogRead(tempPin);
  tempAmount = (val / (float)1023) * 5.0;
  tempAmount *= 100;
  //Serial.println(tempAmount);

  Esp01.readSerial();

  
  if (millis() - start > UPDATE_TIME)
  {
    Esp01.dataToServer(tempAmount);
    start = millis();
  }
}
