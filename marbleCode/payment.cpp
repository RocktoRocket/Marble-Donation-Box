#include "payment.h"

constexpr int coinPulseDelay = 120; // miliseconds between falling edges in pulse train

volatile int paymentImpulseCount = 0;
volatile unsigned long paymentLastImpulse = 0;

void paymentInturupt(){
    paymentImpulseCount += 1;
    paymentLastImpulse = miliseconds();
}

int acceptPayment(){
    // insert the part of payment accepting that runs every cycle
}