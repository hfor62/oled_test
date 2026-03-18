#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Wire.h"

#define SDA_PIN 18
#define SCL_PIN 19

SSD1306Wire display(0x3c, SDA_PIN, SCL_PIN);

// Simulerad logg
String events[] = {
  "Chilli IN",
  "Chilli UT",
  "Herkules IN",
  "Chilli IN",
  "Chilli UT",
  "Herkules UT"
};

int totalEvents = 6;
int startIndex = 0;

void showList(int start) {
  display.clear();

  display.drawString(0, 0, "Catdoor log:");

  for (int i = 0; i < 3; i++) {
    int idx = start + i;
    if (idx < totalEvents) {
      display.drawString(0, 16 + i * 16, events[idx]);
    }
  }

  display.display();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  display.init();
  display.setFont(ArialMT_Plain_10);
}

void loop() {
  showList(startIndex);

  Serial.print("Visar rad: ");
  Serial.println(startIndex);

  startIndex++;

  if (startIndex > totalEvents - 3) {
    startIndex = 0;
  }

  delay(2000);
}