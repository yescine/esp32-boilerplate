#include <Arduino.h>

void blinkLed (byte gpio);
void startingLoop ();

// !touch only led
const byte yellowLed = 32;
byte loopFlag = 0;

void setup() {
  pinMode(yellowLed, OUTPUT);
  Serial.begin(921600);
  Serial.println("\nStarting the setup");
}

void loop() {
  startingLoop();
  blinkLed(yellowLed);
}

void blinkLed (byte gpio) {
  delay(1000);
  digitalWrite(gpio, 0x1);
  delay(1000);
  digitalWrite(gpio, 0x0);
}

void startingLoop(){
  if (loopFlag>0) return;
  Serial.println("Starting the loop...");
  loopFlag++;

}