#ifndef PAYMENT_H_
#define PAYMENT_H_

#include <Arduino.h> 
#include <EEPROM.h> 

void paymentInturupt();
int coinReaderUpdate();
int billReaderUpdate();
int acceptPayment();

#endif //PAYMENT_H_