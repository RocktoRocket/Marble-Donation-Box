#ifndef LIGHTS_H
#define LIGHTS_H

#include <Adafruit_NeoPixel>
#include <arduino.h>

constexpr int padLightStringLength = 20;


class stringLight{
    public:
        uint32_t state[padLightStringLength]; // uint_t is the type that neopixel uses to store colors on the string
        // state holds the current colors of this section of the led string
        int mode;
        void update(unsigned int deltaT);
        void reset();
        stringLight();
    private:
        uint32_t gyro(unsigned int position);
        uint32_t swing(unsigned int position);
        uint32_t step(unsigned int position);
        uint32_t flash(unsigned int position);
        uint32_t redBlink(unsigned int position);
        uint32_t off(unsigned int position);
};

class bulbLight{
    public:
        bool bulbOn;
        int mode;
        void update(unsigned int deltaT);
        void reset();
        bulbLight();
    private:
        unsigned long blinkTime;
        unsigned long blinkCounter;
        bool evenBlink();
        bool stayOn();
        bool stayOff();
};


#endif // LIGHTS_H