#include "button.cpp"

ButtonInterface::ButtonInterface(int Button1, int Button2, int Button3){ // constructor
    pinMode(Button1, INPUT);// setup the pins
    pinMode(Button2, INPUT);
    pinMode(Button3, INPUT);
    pin1 = Button1;
    pin2 = Button2;
    pin3 = Button3;
}

void ButtonInterface::reset(){ // clears variables
    pressed1 = false, pressed2 = false, pressed3 = false;
    int firstPin = 0;
    bool triggered = false;
    bool allThree = false;
}

void ButtonInterface::plainCheck(){ // will update the variables, without keeping track of the button states
    pressed1 = digitalRead(pin1);
    pressed2 = digitalRead(pin2);
    pressed3 = digitalRead(pin3);
    firstPin = 0;
    allThree = false;
    triggered = (pressed1 || pressed2 || pressed3);
}

void ButtonInterface::check(){ // (unused) will update the state of the interface
    bool history = (pressed1 || pressed2 || pressed3);
    pressed1 = digitalRead(pin1) || pressed1;
    pressed2 = digitalRead(pin2) || pressed2;
    pressed3 = digitalRead(pin3) || pressed3;
    if (!history && pressed1){
        firstPin = 1;
    } else if (!history && pressed2){
        firstPin = 2;
    } else if (!history && pressed3){
        firstPin = 3;
    } else if (!history){
        firstPin = 0;
    }
    allThree = (pressed1 && pressed2 && pressed3);
    triggered = (pressed1 || pressed2 || pressed3);
}