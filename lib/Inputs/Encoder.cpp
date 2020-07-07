#include <Arduino.h>
#include <Encoder.h>

//#define ENC_DEBUG

Encoder::Encoder(Joystick_* joystick, int joystickButton1, int joystickButton2, Adafruit_MCP23017* mcp, int mcpPin1, int mcpPin2):
  _joystick(joystick),
  _mcp(mcp),
  _jButtonNumber1(joystickButton1),
  _jButtonNumber2(joystickButton2),
  _mcpPin1(mcpPin1),
  _mcpPin2(mcpPin2),
  _pin1State(PIN_INPUT_RELEASED),
  _pin2State(PIN_INPUT_RELEASED),
  rotary(mcpPin1, mcpPin2) {
}

void Encoder::setState(int mcpPin, uint8_t pinInputState) {
  if(mcpPin == _mcpPin1) _pin1State = pinInputState;
  if(mcpPin == _mcpPin2) _pin2State = pinInputState;

#ifdef ENC_DEBUG
  Serial.print(_pin1State == PIN_INPUT_PRESSED);
  Serial.print(" - ");
  Serial.print(_pin2State == PIN_INPUT_PRESSED);
  Serial.print("    | by pin ");
  Serial.println(mcpPin);
#endif

  auto res = rotary.process(_pin1State == PIN_INPUT_PRESSED, _pin2State == PIN_INPUT_PRESSED);

  if(res == DIR_CW) {
    _joystick->pressButton(_jButtonNumber1);
    delay(50);
    _joystick->releaseButton(_jButtonNumber1);
#ifdef ENC_DEBUG
    Serial.print("Encoder: J Btn ");
    Serial.println(_jButtonNumber1);
#endif
  } else if(res == DIR_CCW) {
    _joystick->pressButton(_jButtonNumber2);
    delay(50);
    _joystick->releaseButton(_jButtonNumber2);
#ifdef ENC_DEBUG
    Serial.print("Encoder: J Btn ");
    Serial.println(_jButtonNumber2);
#endif
  }
}

void Encoder::configureMcp() {
  if(mcpConfigured) return;

  _mcp->pinMode(_mcpPin1, INPUT);
  _mcp->pullUp(_mcpPin1, HIGH);
  _mcp->setupInterruptPin(_mcpPin1, CHANGE);

  _mcp->pinMode(_mcpPin2, INPUT);
  _mcp->pullUp(_mcpPin2, HIGH);
  _mcp->setupInterruptPin(_mcpPin2, CHANGE);

  mcpConfigured = true;
}

void Encoder::debounceTick() {
  // no need to debounce encoder.
}
