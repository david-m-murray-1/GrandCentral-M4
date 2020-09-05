#pragma once
#include "SPI.h"
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

#define TFT_CS_display 2 // chip select GPIO pin 2
#define TFT_CS_touch 3   // chip select GPIO pin 3
#define TIRQ_PIN 6
#define TFT_DC 4
#define TFT_MOSI 51
#define TFT_CLK 52
#define TFT_RST 5
#define TFT_MISO 50

XPT2046_Touchscreen touch(TFT_CS_touch, TIRQ_PIN);
Adafruit_ILI9341 tft(TFT_CS_display, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO); // display

void setup() {
  tft.begin();
  testText();
  Serial.begin(9600);
  touch.begin();
  touch.setRotation(1);
  Serial.print("TFT initialized");
  pinMode(TFT_CS_display, OUTPUT);
  pinMode(TFT_CS_touch, OUTPUT);
}

boolean wastouched = true;

void loop() {
  boolean istouched = touch.touched();
  if (istouched) {
    TS_Point p = touch.getPoint();
    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print("Y = ");
    Serial.print(p.y);
    Serial.print("Z = ");
    Serial.print(p.z);
  }
}

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  delay(1000);
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");   
}
