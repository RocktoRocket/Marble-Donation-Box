#ifndef LIGHTS_H
#define LIGHTS_H

#include <Adafruit_NeoPixel.h>
#include <arduino.h>

constexpr int padLightStringLength = 17;// this is how many lights each pad currently has
constexpr int numberOfBlocks = 3; // remove to use templates 
constexpr int  NOMPIXELS (padLightStringLength * numberOfBlocks); // modify if variable block length



class stringLight{
    public:
        uint32_t state[padLightStringLength]; // uint_t is the type that neopixel uses to store colors on the string
        // state holds the current colors of this section of the led string
        int mode;
        void update(unsigned int deltaT);
        void reset();
        void onPanelTriggered();
        stringLight();
        unsigned long flashStartTime;
    private:
        unsigned long loopTime;
        int loopLength;
        uint32_t gyro(unsigned int position);
        uint32_t swing(unsigned int position);
        uint32_t step(unsigned int position);
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


//template<int numberOfBlocks = 3> // add number of pixels in each block here later if needed

class pixelStrip{ 
    private:
        unsigned long lastTime;
        stringLight blocks[numberOfBlocks];
        Adafruit_NeoPixel pixels;
    public:
        void step();
        void blockSetMode(int block, int newMode);
        pixelStrip(Adafruit_NeoPixel* pixel);
        
    
};


#endif // LIGHTS_H
