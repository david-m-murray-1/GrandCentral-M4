#pragma once
#include "SPI.h"
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_ILI9341.h>
//#include <XPT2046_Touchscreen.h>

#define TFT_CS_display 2 // chip select GPIO pin 2
#define TFT_CS_touch 3   // chip select GPIO pin 3
#define TIRQ_PIN 6
#define TFT_DC 4
#define TFT_MOSI 51
#define TFT_CLK 52
#define TFT_RST 5
#define TFT_MISO 50

// initialize tft & touchscreen
Adafruit_ILI9341 tft(TFT_CS_display, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO); // display
//XPT2046_Touchscreen touch(TFT_CS_touch, TIRQ_PIN);

// Enable/Disable test on TC0, pin A3 on Metro M4, pin A13 on Metro M4 Grand Central
void setup()
{
//enable ili9341 display -- being replaced by ili9341_t3 when testing touch section
  //touch.begin();
  //touch.setRotation(1); 
  Serial.begin(115200);
  delay(1000);
  PWM_init();
  Serial.println("PWM initialized");
  delay(1000);
  Serial.println("pre-display setup");
  delay(1000);
  tft.begin();
  Serial.println("display initialized");
  testText();
}

void loop() {
  Serial.print("entered loop");
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
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
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");   
}

void PWM_init() {
  MCLK->APBAMASK.reg |= MCLK_APBAMASK_TC0;                     // Activate timer TC0
 
  GCLK->PCHCTRL[TC0_GCLK_ID].reg = GCLK_PCHCTRL_CHEN |         // Enable perhipheral channel
                                   GCLK_PCHCTRL_GEN_GCLK0;     // Connect generic clock 0 to TC0

  // Enable the peripheral multiplexer on pin A13
  PORT->Group[g_APinDescription[A13].ulPort].PINCFG[g_APinDescription[A13].ulPin].bit.PMUXEN = 1;
 
  // Set the A3 peripheral multiplexer to peripheral E(4): TC0, Channel 0
  PORT->Group[g_APinDescription[A13].ulPort].PMUX[g_APinDescription[A13].ulPin >> 1].reg |= PORT_PMUX_PMUXE(4);
 
  TC0->COUNT8.CTRLA.reg = TC_CTRLA_PRESCALER_DIV2 |     // Set prescaler to 1024, 120MHz/1024 = 117.19kHz
                          TC_CTRLA_PRESCSYNC_PRESC  |     // Set the reset/reload to trigger on prescaler clock
                          TC_CTRLA_MODE_COUNT8;           // Set the counter to 8-bit mode

  TC0->COUNT8.WAVE.reg = TC_WAVE_WAVEGEN_NPWM;      // Set-up TC0 timer for Normal PWM mode (NPWM)

  TC0->COUNT8.PER.reg = 0xFF;                       // Use PER register as TOP value, set for 457.76Hz PWM
  while (TC0->COUNT8.SYNCBUSY.bit.PER);             // Wait for synchronization

  TC0->COUNT8.CC[0].reg = 127;                      // Set the duty cycle to 50% (CC1 half of PER)
  while (TC0->COUNT8.SYNCBUSY.bit.CC0);             // Wait for synchronization

  TC0->COUNT8.CTRLA.bit.ENABLE = 1;                 // Enable timer TC0
  while (TC0->COUNT8.SYNCBUSY.bit.ENABLE);          // Wait for synchronization
}
