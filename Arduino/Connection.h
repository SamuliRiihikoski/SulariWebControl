#include <SoftwareSerial.h>

struct ESP_chip {

  SoftwareSerial _espSerial =  SoftwareSerial(2,3);
  boolean _debug=true;
   

  void connect_wifi();
  void disconnect_wifi();

  boolean waitForResponse(String target1,  int timeout);
  void clearESP_buffer(int timeout);
  void readSerial();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ESP_chip::connect_wifi()
{
  Serial.println("Creating conection");

  Serial.println("Connecting to network...");
  clearESP_buffer(1000);
  _espSerial.println("AT+GMR");
  waitForResponse("OK",1000);
  
  _espSerial.println("AT+CWMODE=1");  // configure as client
  waitForResponse("OK",1000);
  
  //--- connect
  _espSerial.println("AT+CWJAP=\"LavatanssitIsBack\",\"Koivusalo56\"");
  waitForResponse("OK",10000);
  
  _espSerial.println("AT+CIPMUX=1");         // configure for multiple connections   
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

boolean ESP_chip::waitForResponse(String target1,  int timeout){
    String data;
    char a;
    unsigned long start = millis();
    boolean rValue=false;
    while (millis() - start < timeout) {
        while(_espSerial.available() > 0) {
            a =_espSerial.read();
            if (_debug) Serial.print(a);
            if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target1) != -1) {
            rValue=true;
            break;
        } 
    }
    return rValue;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ESP_chip::clearESP_buffer(int timeout){
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
  if (_espSerial.available())
  {
    delay(1);
    String espBuffer = _espSerial.readStringUntil('\r');
    _espSerial.print("Moikka");
  }
}
