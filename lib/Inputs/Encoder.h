#include <Joystick.h>
#include <Adafruit_MCP23017.h>
#include <Input.h>
#include <Rotary.h>

#ifndef _ENCODER_H_
#define _ENCODER_H_

class Encoder: public Input {
public:
  Encoder(Joystick_* joystick, int joystickButton1, int joystickButton2, Adafruit_MCP23017* mcp, int mcpPin1, int mcpPin2);
  void configureMcp();
  void setState(int mcpPin, uint8_t pinInputState);
  void debounceTick();

private:
  Joystick_* _joystick;
  Adafruit_MCP23017* _mcp;
  int _jButtonNumber1;
  int _jButtonNumber2;
  int _mcpPin1;
  int _mcpPin2;

  uint8_t _pin1State;
  uint8_t _pin2State;

  Rotary rotary;

  bool mcpConfigured = false;
};

#endif
