#ifndef DEV_LED_H
#define DEV_LED_H
#define PIXEL_TYPE WS2812B
// #include <Adafruit_NeoPixel.h>
#include <HomeSpan.h>

class DEV_LED {
public:
  DEV_LED(uint8_t pin, int nPixels);  // Constructor declaration

  void update_LED(int hue, int sat, int val, int pow);

  void update_Effect(int val);

  void effect();

  Pixel *pixel;

private:
  int nPixels;
  int pin;
  int h = 0;
  int s = 0;
  int v = 0;
  int p = 0;
  int eff = 0;
};

DEV_LED::DEV_LED(uint8_t pin, int nPixels)
  : pin(pin), nPixels(nPixels) {
  pixel = new Pixel(pin);   // creates Pixel LED on specified pin
  this->nPixels = nPixels;  // save number of Pixels in this LED Strand
  effect();                 // manually call update() to set pixel with restored initial values
}

void DEV_LED::update_LED(int hue, int sat, int val, int pow) {
  h = hue;
  s = sat;
  v = val;
  p = pow;
  Serial.println("LED " + String(h) + " " + String(s) + " " + String(v) + " " + String(p));
  effect();
}

void DEV_LED::update_Effect(int val) {
  eff = val;
  Serial.println("Effect " + String(eff));
  effect();
}

void DEV_LED::effect() {
  Serial.println("Effect fun " + String(eff));
  Pixel::Color color;
  switch (eff) {
    case 100:
      Serial.println("Effect fun case100 " + String(h) + " " + String(s) + " " + String(v) + " " + String(p));
      pixel->set(color.HSV(h * p, s * p, v * p), nPixels);  // sets all nPixels to the same HSV color
      break;
    case 80:
      while (eff == 80) {
        for (int i = 0; i < nPixels; i++) {
          if (random(100) < 10) {                     // Adjust 10 to control the density of twinkling stars
            pixel->set(color.HSV(h, s, v * 1.2), i);  // Increase brightness for twinkling stars
          } else {
            pixel->set(color.HSV(h, s, v), i);  // Set regular brightness for other LEDs
          }
          delay(50); // Adjust delay to control the speed of color wipe
        }
      }
      break;
    case 60:
      while (eff == 60) {
        for (int i = 0; i < nPixels; i++) {
          float brightness = map(i, 0, nPixels - 1, 0, v);  // Gradually increase brightness
          pixel->set(color.HSV(h, s, brightness), i);
          delay(50);  // Adjust delay to control the speed of color wipe
        }
      }
      break;
    case 40:
      while (eff == 40) {
        for (int i = 0; i < nPixels; i++) {
          float hueShift = map(i, 0, nPixels - 1, 0, 360);  // Shift hue gradually
          float newHue = fmod(h + hueShift, 360);           // Ensure hue wraps around
          pixel->set(color.HSV(newHue, s, v), i);
          delay(50); // Adjust delay to control the speed of color wipe
        }
      }
      break;
    case 20:
      while (eff == 20) {
        for (int i = 0; i < nPixels; i++) {
          int flicker = random(-20, 20);                   // Random flicker intensity
          float flickerV = max(0, min(255, v + flicker));  // Ensure brightness stays within bounds
          pixel->set(color.HSV(h, s, flickerV), i);
          delay(50); // Adjust delay to control the speed of color wipe
        }
      }
      break;
    case 0:
      pixel->set(color.HSV(0, 0, 0), nPixels);  // sets all nPixels to the same HSV color
      break;
    default:
      break;
  };
}

#endif  // DEV_LED_H
