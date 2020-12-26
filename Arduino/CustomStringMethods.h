
struct charArrayMethods
{
  void getData(char* input);
  boolean isMatch(char* input, char* command);
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
