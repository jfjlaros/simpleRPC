INTERFACE("Test function.",
  int, bla, void)
INTERFACE("Add two integers. @P:Value a. @P:Value b. @R:Sum of a and b.",
  int, add, int, int)
INTERFACE("Set LED intensity. @P:Intensity between 0 and 255.",
  void, setLed, int)
