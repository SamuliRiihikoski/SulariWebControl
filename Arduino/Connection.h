#include <SoftwareSerial.h>
#include "CustomStringMethods.h"

struct ESP_chip {

  SoftwareSerial _espSerial =  SoftwareSerial(2,3);
  char inputbuffer[100];
  
  boolean _debug=true;
  int _index = 0;
  bool _saveLetter = false;
   
  void connect_wifi();
  void disconnect_wifi();

  boolean waitForResponse(char* target,  int timeout);
  void clearESP_buffer(int timeout);
  void readSerial();
  void dataToServer(float tempAmount);
  void executeCommand();

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
  
  _espSerial.println("AT+CWMODE=1");  // 1=STATION, 2=ACCESS POINT, 3=BOTH
  waitForResponse("OK",1000);
  
  //--- connect
  _espSerial.println("AT+CWJAP=\"AndroidAP\",\"ywgn9923\"");
  waitForResponse("OK",10000);
  
  _espSerial.println("AT+CIPMUX=1");         // configure for multiple connections   
  waitForResponse("OK",1000);

  _espSerial.println("AT+CWSAP?");         // Show ESP-01 IP
 waitForResponse("OK",1000); 

  _espSerial.println("AT+CIPSERVER=1,80");
  waitForResponse("OK",1000);
 
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

  Serial.println("");
  
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

    executeCommand();
  }
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ESP_chip::dataToServer(float tempAmount)
{
  int string_length = 67;
  
  String data_part = "?sensor=";
  data_part += String(tempAmount);
  
  string_length += data_part.length();
  String atLength = "AT+CIPSEND=0,"; // 67 oikea
  atLength += String(string_length);
  
  Serial.println("Data to server");
  
  _espSerial.println("AT+CIPSTART=0,\"TCP\",\"3.140.78.112\",80");
  waitForResponse("OK",1000);

   _espSerial.println(atLength);
   waitForResponse("OK",1000);

  _espSerial.println("GET /update" + data_part + " HTTP/1.1");  // 20
  _espSerial.println("Host: www.meshare.live"); // 22
  _espSerial.println("Connection: close"); // 17
  _espSerial.println(); // end HTTP header
  delay(2000);
  
  _espSerial.println("AT+CIPCLOSE=0");
  waitForResponse("OK",1000);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ESP_chip::executeCommand()
{
  charArrayMethods cMet;
  if (cMet.isMatch(inputbuffer, "TEMP"))
  {
    dataToServer(1.0);
  }
}
