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
        void onPanelTriggered();
        stringLight();
    private:
        unsigned long loopTime;
        int loopLength;
        uint32_t gyro(unsigned int position);
        uint32_t swing(unsigned int position);
        uint32_t step(unsigned int position);
        unsigned long flashStartTime;
        uint32_t flash();
        uint32_t redBlink();
        uint32_t off();
        uint32_t combine(uint32_t first, uint32_t second);
};

class bulbLight{
    public:
        int lightPin;
        bool bulbOn;
        int mode;
        void update(unsigned int deltaT);
        void reset();
        bulbLight(int pin);
    private:
        unsigned long blinkLength;
        unsigned long blinkCounter;
        bool evenBlink();
        bool stayOn();
        bool stayOff();
};


#endif // LIGHTS_H