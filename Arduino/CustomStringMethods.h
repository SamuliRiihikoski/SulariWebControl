
struct charArrayMethods
{
  void getData(char* input);
  boolean isMatch(char* input, char* command);
  int createGetMessage(char* message, int sensorData); // returns message length
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void charArrayMethods::getData(char* input)
{
  Serial.println("Edit char array"); // TODO
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

boolean charArrayMethods::isMatch(char* input, char* command)
{
  int index = 0;

  while (command[index] != '\0')
  {
    if (command[index] == input[index]) continue;
    else return false;
    
    index++;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int charArrayMethods::createGetMessage(char* message, int sensorData)
{
  int string_length = 0;
  char int_array[4];
  
  sprintf(int_array, "%d", sensorData);
  
  strcpy(message,"GET /update?");

  strcat(message,"sensor=");
  strcat(message,int_array);

  strcat(message," HTTP/1.1\r\n");
  
  return strlen(message);
}
