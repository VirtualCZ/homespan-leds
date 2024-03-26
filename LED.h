#ifndef NEOPIXEL_RGB_H
#define NEOPIXEL_RGB_H

#include <HomeSpan.h>
#include <FastLED.h>
#include "DEV_LED.h"

class LED : public Service::LightBulb {
public:
    Characteristic::On power{0, true};
    Characteristic::Hue H{0, true};
    Characteristic::Saturation S{0, true};
    Characteristic::Brightness V{100, true};

    boolean update() override;

    DEV_LED &dev_led;

    LED(DEV_LED &dev_led); // Constructor declaration

    private:
};

LED::LED(DEV_LED &dev_led) : dev_led(dev_led), Service::LightBulb() {
    V.setRange(0, 100, 1);
    update();
}

boolean LED::update() {
    int p = power.getNewVal();
    int h = H.getNewVal();
    int s = S.getNewVal();
    int v = V.getNewVal();

    dev_led.update_LED(h ,s ,v ,p);

    return true;
}


#endif // NEOPIXEL_RGB_H
