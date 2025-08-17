#include "lights.h"

void stringLight::update(){
if(mode == 1){

} else if(mode == 2){

} else if(mode == 3){

} else if(mode == 4){

} else if(mode == 5){

} else {
for (uint32_t* pixel : state){
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
uint32_t stringLight::flash(unsigned int position){
    
}
uint32_t stringLight::redBlink(unsigned int position){
    
}
uint32_t stringLight::off(unsigned int position){
    
}


void bulbLight::update(unsigned int deltsT){

}
void bulbLight::reset(){
    
}
bulbLight::bulbLight(){
    
}
bool bulbLight::evenBlink();{
    
}
bol bulbLight::stayOn();{
    
}
bol bulbLight::stayOff();{
    
}
