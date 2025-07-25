#include <arduino.h>
#include <vector>


// C++ code
//

const int readyPin = 13; // dont worry about the const, it just prevents the pin numbers from accidentaly being changed later in the code
const int runningPin = 12;
const int readyingPin = 7;

const int endgate1 = 8;
const int endgate2 = 6;
const int endgate3 = 5;
//int endgate4 = 9:

const int redButton1 = 4;
const int redButton2 = 3;
const int redButton3 = 2;


int runUntillFirst(); // these lines let me put the code for the functions later
void finishRunning(int first);
void whileRunning();
int handleMoney();

void setup()
{
  pinMode(readyPin, OUTPUT); 
  pinMode(runningPin, OUTPUT);
  pinMode(readyingPin, OUTPUT);
  
  pinMode(endgate1, INPUT);
  pinMode(endgate2, INPUT);
  pinMode(endgate3, INPUT);
    
  pinMode(redButton1, INPUT);
  pinMode(redButton2, INPUT);
  pinMode(redButton3, INPUT);

  

  Serial.begin(9600);
  Serial.write("ready\n");
}

void loop()
{

  static int first = 1; // static should only initalize the variable the first time loop happens

  int buttonState = 0; 
  int selection = 1;
  while (buttonState == 0) { // wait for a selection to be made with the buttons
    if (digitalRead(redButton1)){
      buttonState++;
      selection = 1;
    }
    if (digitalRead(redButton2)){
      buttonState++;
      selection = 2;
    }
    if (digitalRead(redButton3)){
      buttonState++;
      selection = 3;
    }
  
  digitalWrite(readyPin, HIGH);
  
  delay(10); // Wait for 10 millisecond(s) to give time for the input to change
  }

  Serial.write("running\n"); 
  digitalWrite(readyPin, LOW); // this code runs when a button has been selected
  digitalWrite(runningPin, HIGH); // code here to release the distributer solenoids and power up the motors in the fish ladder 

  first = runUntillFirst();

  finishRunning(first);

  // code here for comparing the selection to the result of the run, and assigning free runs

  Serial.write("done running, reseting...\n");
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(runningPin, LOW);
  digitalWrite(readyingPin, HIGH);

  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(readyingPin, LOW);
  digitalWrite(readyPin, HIGH);
}



int handleMoney(){
  // returns the number of runs that have been paid for.
}

int runUntillFirst() { // runs untill the first end platform is triggered, then returns the number corresponding to the platform
  bool running = true;
  while (running) {
    whileRunning();
    if (digitalRead(endgate1)) {
      running = false;
      return 1;
    }
    if (digitalRead(endgate2)) {
      running = false;
      return 2;
    }
    if (digitalRead(endgate3)) {
      running = false;
      return 3;
    }
    
  }
}

void finishRunning(int first) { // after the first gate triggers, wait for the other two tracks to finish
  bool gate1 = false, gate2 = false, gate3 = false;
  if (first = 1){ // one of the tracks has finished at this point
    gate1 = true;
  else if (first = 2){
    gate2 = true;
  }
  else if (first = 3){
    gate3 = true;
  }
  else{
    gate1 = true;
    gate2 = true;
    gate3 = true;
  }
  while (!(gate1 && gate2 && gate3)) { // wait for all tracks to be completed
    whileRunning();
    gate1 = gate1 || digitalRead(endgate1); // this will set the value to true if the input is true,
    gate2 = gate2 || digitalRead(endgate2); // if the input is false then nothing will happen
    gate3 = gate3 || digitalRead(endgate3);
  }
}

void whileRunning(){
  // do running stuff here (includes running light code and begining to reset the balls with the auger)
}

