#include <Arduino.h>
#include <driver/gpio.h>
#include <WiFi.h>
#include <RGBLed.h>
// --define env avr
#define WIFI_SSID "wifi_network_name"
#define WIFI_PASSWORD "wifi_password"

void blinkLed (byte gpio);
void startingLoop ();
void connectWiFi (byte gpio);

// !touch only led
bool WiFiConnected = false;
const byte yellowLed = GPIO_NUM_32;
const byte WifiLed = GPIO_NUM_12;
byte loopFlag = 0;

const byte rgbLed[] = {GPIO_NUM_26,GPIO_NUM_25,GPIO_NUM_23};
RGBLed rainbow(rgbLed[0],rgbLed[1],rgbLed[2],false);

void setup() {
  pinMode(yellowLed, OUTPUT);
  pinMode(WifiLed, OUTPUT);
  Serial.begin(921600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("\nStarting the setup");

}

void loop() {
  startingLoop();
  connectWiFi(WifiLed,WiFiConnected);
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

void connectWiFi(byte gpio,bool flag) {
  if (WiFi.status() == WL_CONNECTED && !flag) {
    Serial.println("Wifi Connected");
    digitalWrite(gpio, HIGH);
    flag = true;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    digitalWrite(gpio, !digitalRead(gpio));
    delay(1000);
    flag = false;
  }
}