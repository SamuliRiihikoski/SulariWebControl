
struct ModifyString 
{
  String cleanString(String input);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String ModifyString::cleanString(String input)
{
  int inputLength = input.length();
  int beginning = input.indexOf(':') + 1;
  String newString = input.substring(beginning, inputLength);

  return newString;
}
