#include <SoftwareSerial.h>
#include "CustomStringMethods.h"

struct ESP_chip {

  SoftwareSerial _espSerial =  SoftwareSerial(2,3);
  char inputbuffer[100];
  
  boolean _debug=true;
  ModifyCharArray editInput;
  int _index = 0;
  bool _saveLetter = false;
   
  void connect_wifi();
  void disconnect_wifi();

  boolean waitForResponse(char* target,  int timeout);
  void clearESP_buffer(int timeout);
  void readSerial();

  ESP_chip()
  {
    _espSerial.begin(115200);
  }

 };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ESP_chip::connect_wifi()
{
  Serial.println("Connecting to Wifi network...");
  clearESP_buffer(1000);
  _espSerial.println("AT+GMR");
  waitForResponse("OK",1000);
  
  _espSerial.println("AT+CWMODE=2");  // configure as access point. If you have router then mode=1 is better with unchecking /* */ part
  waitForResponse("OK",1000);
  /*
  //--- connect
  _espSerial.println("AT+CWJAP=\"NetworkName\",\"Password\"");
  waitForResponse("OK",10000);
  
  _espSerial.println("AT+CIPMUX=1");         // configure for multiple connections   
  waitForResponse("OK",1000);
*/

  _espSerial.println("AT+CWSAP?");         // Show ESP-01 IP
 waitForResponse("OK",1000); 
/*  
  _espSerial.println("AT+CIPSERVER=1,80");
  waitForResponse("OK",1000);
  */
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ESP_chip::disconnect_wifi()
{
  // TODO 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

boolean ESP_chip::waitForResponse(char* target,  int timeout)
{
  boolean match = false;
  boolean rValue = false;
  int index = 0;
  unsigned long start = millis();
  char a;

  while (millis() - start < timeout)
  {
    while (_espSerial.available())
    {
      a = _espSerial.read();
      if (_debug) Serial.print(a);
      
      if (target[index] == a) { match = true; index++; }
      else { match = false; index = 0; }
    }

    if (match) { rValue = true; break; }
  }
  
  return rValue;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ESP_chip::clearESP_buffer(int timeout)
{
    long t=millis();
    char c;
    
    while (t+timeout>millis())
    {
      if (_espSerial.available()){
        c=_espSerial.read();
        if (_debug) Serial.print(c);
      }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ESP_chip::readSerial()
{ 
  int incomingByte = 0;
  
  if (_espSerial.available())
  {
    delay(1);
    
    incomingByte = _espSerial.read();
    inputbuffer[_index] = incomingByte;

    if (_saveLetter) _index++;
    if (inputbuffer[_index] == ':') _saveLetter = true;
  }
  else if (_saveLetter == true)
  {
    inputbuffer[_index + 1] = '\0';
    _saveLetter = false;
    _index = 0;
    Serial.print("Command received: ");
    Serial.println(inputbuffer);
  }
  
}
