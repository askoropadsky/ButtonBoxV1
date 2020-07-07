#include <Joystick.h>
#include <Adafruit_MCP23017.h>
#include <Input.h>

#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button: public Input {
public:
  Button(Joystick_* joystick, int joystickButton, Adafruit_MCP23017* mcp, int mcpPin);
  void setState(int mcpPin, uint8_t pinInputState);
  void configureMcp();
  void debounceTick();

protected:
  Joystick_* _joystick;
  int _jButtonNumber;
  Adafruit_MCP23017* _mcp;
  int _mcpPin;
  uint8_t _state;

  bool configured = false;

  unsigned long reportStateAfterMillis;
};

#endif
