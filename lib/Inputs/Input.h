#include <Arduino.h>

#ifndef _INPUT_H_
#define _INPUT_H_

// PIN_INPUT_STATE
#define PIN_INPUT_PRESSED  0
#define PIN_INPUT_RELEASED  1

class Input {
public:
  virtual void setState(int mcpPin, uint8_t pinInputState);
  virtual void configureMcp();
  virtual void debounceTick();

protected:
  static const unsigned long debounceDelay = 50;
};

#endif
