#include "lights.h"



constexpr int default_length_of_lighting_patterns = 1000; // milliseconds

void stringLight::update(){
    loopTime = millis()%loopLength;
    if(mode == 1){
        for (int i = 0; i < padLightStringLength; i++){
            state[i] = gyro(i);
        }
    } else if(mode == 2){
        for (int i = 0; i < padLightStringLength; i++){
            state[i] = swing(i);
        }
    } else if(mode == 3){
        for (int i = 0; i < padLightStringLength; i++){
            state[i] = step(i);
        }
    } else if(mode == 4){
        for (uint32_t &pixel: state){ // this format works for modes that are the same for each pixel
            pixel = redBlink();
        }
    } else {
        for (uint32_t &pixel: state){
            pixel = off();
        }
    }
    //aftereffects
    for (uint32_t &pixel: state){
        pixel = combine(pixel, flash());
    }
}

void stringLight::reset(){
    mode = 5;
    state[] = {0};
}

stringLight::stringLight(){
    mode = 5;
    state[] = {0};
    loopTime = 0;
    loopLength = default_length_of_lighting_patterns; 
}


uint32_t stringLight::gyro(unsigned int position){
 
}

uint32_t stringLight::swing(unsigned int position){
    
}

uint32_t stringLight::step(unsigned int position){
    
}

uint32_t stringLight::flash(){
    
}

uint32_t stringLight::redBlink(){
    if (blinkTime > loopLength/2){ //blink evenly
        return 0x800000; // half brightness red
    } else{
        return 0;
    }
}

uint32_t stringLight::off(){
    return 0;
}

uint32_t combine(uint32_t first, uint32_t second){
    uint16_t r,b,g;
    r = first & 0xFF0000;
    b = first & 0x00FF00;
    g = first & 0x0000FF;
    r += second & 0xFF0000;
    b += second & 0x00FF00;
    g += second & 0x0000FF;
    if (r > 255) r = 255;
    if (b > 255) r = 255;
    if (g > 255) r = 255;
    return ((uint32_t)r << 16) | ((uint32_t)b << 8) | g;
}


// stuff for single leds
void bulbLight::update(unsigned int deltsT){
    blinkCounter+=deltaT;
    blinkCounter%=blinkLength;
    if (mode == 1){
        bulbOn = evenBlink();
    } else if (mode == 2){
        bulbOn = stayOn();
    } else{
        bulbOn = stayOff();
    }

    if(bulbOn){
        digitalWrite(lightPin, HIGH);
    }else {
        digitalWrite(lightPin, LOW);
    }
}

void bulbLight::reset(){
    blinkCounter = 0;
    mode = 1;
}

bulbLight::bulbLight(int pin){
    lightPin = pin;
    bulbOn = false;
    mode = 1;
    blinkLength = 1000;
    blinkCounter = 0;
}

bool bulbLight::evenBlink(){
    if (blinkCounter > blinkLength/2){
        return true;
    } else {
        return false;
    }
}

bool bulbLight::stayOn(){
    return true;
}

bool bulbLight::stayOff(){
    return false;
}


void pixelStrip::step(){

}

pixelStrip::pixelStrip(int pin,){
    pixels.setPin(pin);
    for (int i = 0; i < numberOfBlocks; i++){
        blocks[i] = stringLight() // this neds to be changed if block length is variable
    }
}
