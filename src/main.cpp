#include <Arduino.h>
#include <driver/gpio.h>
#include <WiFi.h>
#include <RGBLed.h>
#include "node_env.h"

// --define env avr

void blinkLed (byte gpio);
void startingLoop ();
void connectWiFi (byte gpio);

// !touch only led
bool WiFiConnected = false;
const byte yellowLed = GPIO_NUM_17;
const byte WifiLed = GPIO_NUM_16;
const byte buttonRed = GPIO_NUM_14;

byte loopFlag = 0;

const byte rgbLed[] = {GPIO_NUM_26,GPIO_NUM_25,GPIO_NUM_23};
RGBLed rainbow(rgbLed[0],rgbLed[1],rgbLed[2],false);

void setup() {
  pinMode(yellowLed, OUTPUT);
  pinMode(WifiLed, OUTPUT);
  pinMode(buttonRed, INPUT_PULLUP); //? high at default

  Serial.begin(921600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("\nStarting the setup");

}

void loop() {
  startingLoop();
  connectWiFi(WifiLed);
  blinkLed(yellowLed);
  rainbow.crossFade(255, 0, 0, 0, 255, 255, 8, 400);

  if(digitalRead(buttonRed)==LOW) Serial.println("\nButton pressed");
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

void connectWiFi(byte gpio) {  
  if (WiFi.status() == WL_CONNECTED && !WiFiConnected) {
    Serial.println("Wifi Connected");
    digitalWrite(gpio, HIGH);
    WiFiConnected = true;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("wifi not connected");
    digitalWrite(gpio, !digitalRead(gpio));
    delay(1000);
    WiFiConnected = false;
  }
}