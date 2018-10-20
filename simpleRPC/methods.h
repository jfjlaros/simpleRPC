INTERFACE("Receive a value and echo it back. @P: Value. @R:Value.",
  int, ping, int)
INTERFACE("Test function. @R:The number 1.",
  int, testInt, void)
INTERFACE("Test function. @R:The constant phi.",
  float, testFloat, void)
INTERFACE("Add two integers. @P:Value a. @P:Value b. @R:Sum of a and b.",
  int, add, int, int)
INTERFACE("Set LED intensity. @P:Intensity between 0 and 255.",
  void, setLed, int)
