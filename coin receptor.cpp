#include <Arduino.h> 
#include <EEPROM.h> 
//#include <TM1637Display.h> 
//Define the pins for the TM1637 4-digit display 
//#define CLK 3 
//#define DIO 4 
//initialize the TM1637 display object 
//TM1637Display display(CLK, DIO); 
//variables 
int i; 
volatile int impulsCount=0; //count pulses from coin reader 
float total_amount=0; //store total amount entered into coin reader 
unsigned long lastUpdate = 0; //used for timing 
unsigned long timeOfLastImpulse = 0; 
//Interrupt service routine to increment pulse count 
void incomingImpuls() 
{ 
impulsCount = impulsCount+1; 
timeOfLastImpulse = millis(); 
} 
void setup() { 
Serial.begin(9600); //initialize Serial comjunication for debugging 
attachInterrupt(digitalPinToInterrupt(2), incomingImpuls, FALLING); 
//attatch interrupt to pin 2 for the FALLING edge signal, pulse input 
EEPROM.get(0, total_amount);  // Load previously saved amount from 
EEPROM at address 0 
Serial.println("readymessage"); 
// Set display brightness and clear it 
//display.setBrightness(0x0f);// Max brightness 
//display.clear(); //clear display on startup 
} 
void loop() { 
  // Run every 500 ms 
  if (millis() - lastUpdate >= 500 && millis()-timeOfLastImpulse > 160) { 
  int impulses = impulsCount; 
  lastUpdate = millis(); 
  Serial.println(millis()); 
  Serial.println(impulsCount); 
  // Update total based on the number of impulses detected 
  if (impulses = 1) { 
    total_amount += 0.01; // penny 
  }
  else if (impulses = 2){
    total_amount += 0.10; //dime 
  }
  else if (impulses = 3){
    total_amount += 0.05; //nickel 
  }
  else if (impulses = 4){
    total_amount += 0.25; //quarter 
  } 
  else {
    total_amount += 0; // no coin
  }
  //if any impulses were handled, save the new total and reset impulse 
  counter 
  if (impulses > 0 && impulses <= 4) { 
  //EEPROM.put(0, total_amount);  // Save to EEPROM 
  impulsCount = 0; //reset counter 
  } 
  // Display total amount (in cents) if desired 
  int displayValue = (int)(total_amount * 100); // Convert to integer 
  cents 
  Serial.println(displayValue); 
  //display.showNumberDec(displayValue, false); 
} 
}
