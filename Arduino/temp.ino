#include "Connection.h"

ESP_chip Esp01; // Handle ESP-01 methods

const int tempPin = A0;
int val = 0;
float tempVolt = 0;

struct Tieto {
  int luku;
};

void setup() 
{
  Serial.begin(9600);
  
  Esp01.connect_wifi();
}

void loop() 
{
  val = analogRead(tempPin);
  tempVolt = (val / (float)1023) * 5.0;
  //Serial.println(tempVolt * 100);

  Esp01.readSerial();
}
