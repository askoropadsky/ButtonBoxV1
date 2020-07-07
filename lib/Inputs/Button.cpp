#include <Button.h>
#include <Arduino.h>

Button::Button(Joystick_* joystick, int joystickButton, Adafruit_MCP23017* mcp, int mcpPin):
  _joystick(joystick),
  _jButtonNumber(joystickButton),
  _mcp(mcp),
  _mcpPin(mcpPin),
  _state(PIN_INPUT_RELEASED),
  reportStateAfterMillis(0) {
}

//todo: add debounce logic
void Button::setState(int mcpPin, uint8_t state) {
  if(mcpPin != _mcpPin) return;

  // if(state == PIN_INPUT_PRESSED) {
  //   Serial.print("--< Joystick button ");
  //   Serial.print(_jButtonNumber);
  //   Serial.print(" ");
  //   Serial.println(state);
  // }
  //_joystick->setButton(_jButtonNumber, val);

  _state = state;
  reportStateAfterMillis = millis() + debounceDelay;
}

void Button::configureMcp() {
  if(configured) return;

  _mcp->pinMode(_mcpPin, INPUT);
  _mcp->pullUp(_mcpPin, HIGH);
  _mcp->setupInterruptPin(_mcpPin, CHANGE);

  configured = true;
}

void Button::debounceTick() {
  if(reportStateAfterMillis != 0 && millis() >= reportStateAfterMillis) {
    reportStateAfterMillis = 0;

    int val = 0;
    if(_state == PIN_INPUT_PRESSED) val = 1;
    _joystick->setButton(_jButtonNumber, val);

    // Serial.print("--> Joystick button ");
    // Serial.print(_jButtonNumber);
    // Serial.print(" ");
    // Serial.println(val);
  }
}
