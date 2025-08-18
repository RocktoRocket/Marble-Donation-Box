#include "lights.h"

void stringLight::update(){
if(mode == 1){

} else if(mode == 2){

} else if(mode == 3){

} else if(mode == 4){

} else if(mode == 5){

} else {
for (uint32_t pixel : state){
pixel = off();
}
}

}
void stringLight::reset(){
    
}
stringLight::stringLight(){
    
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
    if (millis()%1000 > 500){
        return 0x800000; // half brightness red
    } else{
        return 0;
    }
}
uint32_t stringLight::off(){
    return 0;
}


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
}
void bulbLight::reset(){
    
}
bulbLight::bulbLight(){
    bulbOn = false;
    mode = 1;
    blinkLength = 1000;
    blinkCounter = 0;
    reset();
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
