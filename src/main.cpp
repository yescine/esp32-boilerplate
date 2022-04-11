#include <Arduino.h>
#include <driver/gpio.h>
#include <RGBLed.h>
void blinkLed (byte gpio);
void startingLoop ();

// !touch only led
const byte yellowLed = GPIO_NUM_32;
byte loopFlag = 0;

const byte rgbLed[] = {GPIO_NUM_26,GPIO_NUM_25,GPIO_NUM_23};
RGBLed rainbow(rgbLed[0],rgbLed[1],rgbLed[2],false);

void setup() {
  pinMode(yellowLed, OUTPUT);
  Serial.begin(921600);
  Serial.println("\nStarting the setup");
}

void loop() {
  startingLoop();
  blinkLed(yellowLed);
  rainbow.crossFade(255, 0, 0, 0, 255, 255, 8, 400);
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