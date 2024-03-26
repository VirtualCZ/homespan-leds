#ifndef EFFECT_H
#define EFFECT_H

#include <HomeSpan.h>
#include <FastLED.h>
#include "DEV_LED.h"

class Effect : public Service::LightBulb {
public:
    Characteristic::On power{0, true};
    Characteristic::Hue H{0, true};
    Characteristic::Saturation S{0, true};
    Characteristic::Brightness V{100, true};

    boolean update() override;

    DEV_LED &dev_led;

    Effect(DEV_LED &dev_led); // Constructor declaration

    private:
};

Effect::Effect(DEV_LED &dev_led) : dev_led(dev_led), Service::LightBulb() {
    V.setRange(0, 100, 10);
    update();
}

boolean Effect::update() {
    int v = V.getNewVal();

    dev_led.update_Effect(v);

    return true;
}

#endif // EFFECT_H
