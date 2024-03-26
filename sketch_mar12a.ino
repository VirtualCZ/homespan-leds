/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2022 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/

// HomeSpan Addressable RGB LED Examples.  Demonstrates use of:
//
//  * HomeSpan Pixel Class that provides for control of single-wire addressable RGB and RGBW LEDs, such as the WS2812 and SK6812
//  * HomeSpan Dot Class that provides for control of two-wire addressable RGB LEDs, such as the APA102 and SK9822
//
// IMPORTANT:  YOU LIKELY WILL NEED TO CHANGE THE PIN NUMBERS BELOW TO MATCH YOUR SPECIFIC ESP32/S2/C3 BOARD
//

#if defined(CONFIG_IDF_TARGET_ESP32)
#define DEVICE_SUFFIX ""

#endif

#include "DEV_LED.h"
#include "Effect.h"
#include "LED.h"
#include "HomeSpan.h"
#include <FastLED.h>

///////////////////////////////
// EffectClass effect;
// NeoPixel_RGB led;


void setup() {
  DEV_LED* dev_led;
  LED* led;
  Effect* effect;

  dev_led = new DEV_LED(13, 120);

  Serial.begin(115200);

  homeSpan.enableOTA("13245678");

  homeSpan.begin(Category::Lighting, "RGB strips" DEVICE_SUFFIX);

  SPAN_ACCESSORY();  // create Bridge (note this sketch uses the SPAN_ACCESSORY() macro, introduced in v1.5.1 --- see the HomeSpan API Reference for details on this convenience macro)

  SPAN_ACCESSORY("RGB strip 1");
    led = new LED(*dev_led);  // create 8-LED NeoPixel RGB Strand with full color control

  SPAN_ACCESSORY("Effect Setter 1");
    effect = new Effect(*dev_led);  // create 8-LED NeoPixel RGB Strand with full color control
}

///////////////////////////////

void loop() {
  homeSpan.poll();
}

///////////////////////////////