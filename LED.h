#ifndef NEOPIXEL_RGB_H
#define NEOPIXEL_RGB_H

#include <HomeSpan.h>
#include <FastLED.h>

class NeoPixel_RGB : public Service::LightBulb {
public:
    Characteristic::On power{0, true};
    Characteristic::Hue H{0, true};
    Characteristic::Saturation S{0, true};
    Characteristic::Brightness V{100, true};

    NeoPixel_RGB(); // Constructor declaration

    boolean update() override;

    std::array<int, 4> get_changes(int val1, int val2, int val3, int val4){
      Serial.println("LED " + String(val1) + " " + String(val2) + " " + String(val3) + " " + String(val4));
      return {val1, val2, val3, val4};
    }

    private:
};


NeoPixel_RGB::NeoPixel_RGB() : Service::LightBulb() {
    V.setRange(0, 100, 1);
    update();
}

boolean NeoPixel_RGB::update() {
    int p = power.getNewVal();
    int h = H.getNewVal();
    int s = S.getNewVal();
    int v = V.getNewVal();

    get_changes(h,s,v,p);

    return true;
}


#endif // NEOPIXEL_RGB_H
