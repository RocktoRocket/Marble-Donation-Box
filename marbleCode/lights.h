#ifndef LIGHTS_H
#define LIGHTS_H

#include <Adafruit_NeoPixel>

constexpr int padLightStringLength = 20;


class stringLight{
    public:
        uint32_t state[padLightStringLength]; // uint_t is the type that neopixel uses to store colors on the string
        // state holds the current colors of this section of the led string
        int mode;
        void update(unsigned int deltaT);
        void reset();
    private:
        
        void (*patternPointer[])(void) = {
            gyro,
            step,
            swing,
            flash,
            redBlink
        }
};

class bulbLight{
    public:
        bool state;
        int mode;
        void update(unsigned int deltaT);
        void reset();
    private:
        unsigned long blinkTime;
        unsigned long blinkCounter;
        bulbLight();
};


#endif // LIGHTS_H