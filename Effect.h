#ifndef EFFECTCLASS_H
#define EFFECTCLASS_H

#include <HomeSpan.h>
#include <FastLED.h>
#include "LED.h"

struct EffectClass : Service::LightBulb {
    Characteristic::On pwr{0,true};
    Characteristic::Hue Hu{0,true};
    Characteristic::Saturation Sa{0,true};
    Characteristic::Brightness Br{100,true};
    NeoPixel_RGB &neopixel;
    int nPixels;
    Pixel *pixel;

    static void updateReceived() {
        Serial.println("LED update received!");
        // You can perform any necessary actions here
    }

    EffectClass(NeoPixel_RGB &neopixel, uint8_t pin, int nPixels) : neopixel(neopixel), Service::LightBulb() {
        this->nPixels = nPixels;
        pixel = new Pixel(pin);
        Br.setRange(0, 100, 20);
        update();
    }

    void effect(int val){
      int h, s, v, p;
      switch (val){
        case 100:
          Pixel::Color color;
          h = neopixel.H.getVal();
          s = neopixel.S.getVal();
          v = neopixel.V.getVal();
          p = neopixel.power.getVal();

          pixel->set(color.HSV(h*p, s*p, v*p), nPixels);
          break;
        case 80:
          break;
        case 60:
          break;
        case 40:
          break;
        case 20:
          break;
        case 0:
          pixel->set(color.HSV(h*p, s*p, v*0), nPixels);
          break;
        default:
          break;
      };
    }

    boolean update() override {
        int pw = pwr.getNewVal();
        float hu = Hu.getNewVal<float>();
        float sa = Sa.getNewVal<float>();
        float br = Br.getNewVal<float>();
        effect(br);

        // neopixel.power.setVal(pw);
        // neopixel.H.setVal(hu);
        // neopixel.S.setVal(sa);
        // neopixel.V.setVal(br);

        Serial.println("Effect " + String(hu) + " " + String(sa) + " " + String(br) + " " + String(pw));
        Serial.println("LED in effect " + String(neopixel.H.getVal()) + " " + String(neopixel.S.getVal()) + " " + String(neopixel.V.getVal()) + " " + String(neopixel.power.getVal()));

        return true;
    }
};

#endif // EFFECTCLASS_H
