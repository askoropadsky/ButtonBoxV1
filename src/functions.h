#include <Arduino.h>
#include <Joystick.h>
#include <Adafruit_MCP23017.h>
#include <Button.h>
#include <Encoder.h>

Joystick_ joystick;
Adafruit_MCP23017 mcp0;
Adafruit_MCP23017 mcp1;

// Black Box buttons
Button bb1(&joystick, 0, &mcp0, 0);
Button bb2(&joystick, 1, &mcp0, 1);
Button bb3(&joystick, 2, &mcp0, 2);
Button bb4(&joystick, 3, &mcp0, 3);
Button bb5(&joystick, 4, &mcp0, 4);
Button bb6(&joystick, 5, &mcp0, 5);
Button bb7(&joystick, 6, &mcp0, 6);
Button bb8(&joystick, 7, &mcp0, 7);
Button bb9(&joystick, 8, &mcp0, 8);
Button bb10(&joystick, 9, &mcp0, 9);

// Some buttons:
Button btn1(&joystick, 10, &mcp0, 10); // Ignition
Button btn2(&joystick, 11, &mcp0, 11); // Pit limiter
Button btn3(&joystick, 12, &mcp0, 12); // bb toggle up
Button btn4(&joystick, 13, &mcp0, 13); // bb toggle down
Button btn5(&joystick, 14, &mcp0, 14); // pit config
Button btn6(&joystick, 15, &mcp0, 15); // tow

//Encoder
Encoder enc1(&joystick, 16, 17, &mcp1, 0, 1);
Button encButton(&joystick, 18, &mcp1, 2);

// another buttons
Button btn7(&joystick, 19, &mcp1, 3); // Engine start
Button btn8(&joystick, 20, &mcp1, 4); // no bumps
Button btn9(&joystick, 21, &mcp1, 5); // thanks
Button btn10(&joystick, 22, &mcp1, 6); // hold line
Button btn11(&joystick, 23, &mcp1, 7); // ok
Button btn12(&joystick, 24, &mcp1, 8);
Button btn13(&joystick, 25, &mcp1, 9);
Button btn14(&joystick, 26, &mcp1, 10);
Button btn15(&joystick, 27, &mcp1, 11);
Button btn16(&joystick, 28, &mcp1, 12); // sorry
Button btn17(&joystick, 29, &mcp1, 13); // welcome
Button btn18(&joystick, 30, &mcp1, 14); // no problem
Button btn19(&joystick, 31, &mcp1, 15); // position back

#define BUTTONS_COUNT 32
Input* inputs[BUTTONS_COUNT] = {
  &bb1, &bb2, &bb3, &bb4, &bb5, &bb6, &bb7, &bb8, &bb9, &bb10,
  &btn1, &btn2, &btn3, &btn4, &btn5, &btn6, &enc1, &enc1, &encButton,
  &btn7, &btn8, &btn9, &btn10, &btn11, &btn12, &btn13, &btn14, &btn15, &btn16, &btn17, &btn18, &btn19
};

// Pro Micro interruption pins: 3, 2, 0, 1, 7
uint8_t mcp0InterruptPin = 0;
uint8_t mcp1InterruptPin = 7;
volatile boolean mcp0Interrupted = false;
volatile boolean mcp1Interrupted = false;

void intMcp0Callback() {
  mcp0Interrupted = true;
}

void intMcp1Callback() {
  mcp1Interrupted = true;
}

void handleInterrupt(uint8_t mcpIndex, Adafruit_MCP23017 &mcp) {
  uint8_t pin = mcp.getLastInterruptPin();

  uint8_t val = mcp.digitalRead(pin);
  // Serial.print("i on mcp");
  // Serial.print(mcpIndex);
  // Serial.print(" on pin: ");
  // Serial.println(pin);

  if(0 <= pin && pin <= 15) {
    int inputIndex = mcpIndex*16 + pin;
    Input* input = inputs[inputIndex];
    if(input != NULL) input->setState(pin, val);
  }
}

void readAndReportInitialButtonsState(uint16_t mcp0Pins, uint16_t mcp1Pins) {
  //todo:
}
