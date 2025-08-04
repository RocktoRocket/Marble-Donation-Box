#include "payment.h"

constexpr int coinPulseDelay = 120; // miliseconds between falling edges in pulse train

volatile int coinPaymentImpulseCount = 0;


void paymentInturuptCoin(){
    coinPaymentImpulseCount += 1;
}

int coinReaderUpdate(){
    constexpr int coinConversions[] = {0,1,10,5,25};
    static int lastPaymentCount = 0;
    if (coinPaymentImpulseCount - lastPaymentCount){ // if the number of pulses has not changed
        lastPaymentCount = coinPaymentImpulseCount;
        return 0;
    } else { // if the pulses have stopped coming
        if (paymentImpulseCount < 0 || paymentImpulseCount > 4){
            paymentImpulseCount = 0;
        }
        int amount = coinConversions[coinPaymentImpulseCount];
        coinPaymentImpulseCount = 0;
        Serial.write(amount + " cents recived from coin reader\n");
        return amount;
    }
}

int billReaderUpdate(){
    //code here
}

int acceptPayment(){
    int centsThisCycle = 0;

    static unsigned long lastCoinCheck = 0;
    if (miliseconds()-lastCoinCheck < coinPulseDelay){
        centsThisCycle += coinReaderUpdate();
        lastCoinCheck = miliseconds();
    }
    
    //something for the bill reader here

    return centsThisCycle;
}