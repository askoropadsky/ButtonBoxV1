/*
 * Rotary encoder library for Arduino.
 */

#ifndef Rotary_h
#define Rotary_h

#include "Arduino.h"

// Enable this to emit codes twice per step.
// #define HALF_STEP

// Configure pins as inputs
// #define CONFIGURE_PINS

// Enable weak pullups
// #define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Counter-clockwise step.
#define DIR_CCW 0x20

class Rotary
{
  public:
    Rotary(char, char);
    unsigned char process();
    unsigned char process(unsigned char pin1State, unsigned char pin2State);

  private:
    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;
};

#endif
