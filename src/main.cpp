#include "functions.h"

void setup() {
  //delay(5000);
  Serial.begin(921600);
  Serial.println("Setup start");

  // Wire.setClock(100000L); // set i2c speed to 100k
  Wire.setClock(400000L); // set i2c speed to 400k
  // Wire.setClock(1700000L); // set i2c speed to 1.7M

  mcp0.begin(0);
  mcp1.begin(4);

  for(int i = 0 ; i < BUTTONS_COUNT ; i++) {
    if(inputs[i] != NULL) inputs[i]->configureMcp();
  }

  joystick.begin(true);

  pinMode(mcp0InterruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(mcp0InterruptPin), intMcp0Callback, FALLING);

  pinMode(mcp1InterruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(mcp1InterruptPin), intMcp1Callback, FALLING);

  //clear mcp interrupts
  mcp0.setupInterrupts(true, false, LOW);
  mcp1.setupInterrupts(true, false, LOW);

  auto mcp0Pins = mcp0.readGPIOAB();
  auto mcp1Pins = mcp1.readGPIOAB();

  readAndReportInitialButtonsState(mcp0Pins, mcp1Pins);

  Serial.println("Setup complete");
}

void loop() {
  if(mcp0Interrupted) {
    mcp0Interrupted = false;
    handleInterrupt(0, mcp0);
  }

  if(mcp1Interrupted) {
    mcp1Interrupted = false;
    handleInterrupt(1, mcp1);
  }

  for(int i = 0 ; i < BUTTONS_COUNT ; i++) {
    if(inputs[i] != NULL) inputs[i]->debounceTick();
  }
}
