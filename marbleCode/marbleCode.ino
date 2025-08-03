#include <arduino.h>
#include "buttons.h"

// C++ code
//

// placeholder pin numbers change these please
constexpr pin_size_t readyPin = 13; // saving pinout numbers for later
constexpr pin_size_t runningPin = 12; // these three are for testing purposes
constexpr pin_size_t readyingPin = 7;

constexpr pin_size_t endgate1 = 8;
constexpr pin_size_t endgate2 = 6;
constexpr pin_size_t endgate3 = 5;

constexpr pin_size_t redButton1 = 4;
constexpr pin_size_t redButton2 = 3;
constexpr pin_size_t redButton3 = 2;

constexpr pin_size_t buttonLight1 = 9;
constexpr pin_size_t buttonLight2 = 10;
constexpr pin_size_t buttonLight3 = 11;


constexpr pin_size_t distributerDonePin = 23; // the limit switch on the third distributer section
constexpr pin_size_t marbleRelease = 24;
constexpr pin_size_t distributerReset = 25;
constexpr pin_size_t augerMotor = 26;
constexpr pin_size_t stairMotor = 27;
constexpr pin_size_t gyroMotor = 28;



ButtonInterface UI(redButton1, redButton2, redButton3);
ButtonInterface endPlates(endgate1, endgate2, endgate3);
int credits = 1; // run once on startup to test the system
int state = 0;

void setup()
{
  pinMode(readyPin, OUTPUT); // these three are placeholders
  pinMode(runningPin, OUTPUT);
  pinMode(readyingPin, OUTPUT);
  
  pinMode(endgate1, INPUT);
  pinMode(endgate2, INPUT);
  pinMode(endgate3, INPUT);

  pinMode(redButton1, INPUT);
  pinMode(redButton2, INPUT);
  pinMode(redButton3, INPUT);

  pinMode(buttonLight1, OUTPUT);
  pinMode(buttonLight2, OUTPUT);
  pinMode(buttonLight3, OUTPUT);

  pinMode(distributerDonePin, OUTPUT);
  pinMode(marbleRelease, OUTPUT);
  pinMode(distributerReset, OUTPUT);
  pinMode(augerMotor, OUTPUT);
  pinMode(stairMotor, OUTPUT);
  pinMode(gyroMotor, OUTPUT);

  Serial.begin(9600);
  Serial.write("ready\n");

}

void loop(){ // this is where code goes to run each cycle
    doStates(state, credits, UI, endPlates);
    credits += acceptPayment();
    // lights
}



void doStates(int &state, int &credits, ButtonInterface &UI, ButtonInterface &endPlates){
    static unsigned long timerStartTime = 0;
    if (state = 0){ // wait for credits/payment
        if (credits > 0){// on exit of waiting for payment
            credits--;
           
            state = 1;
        }
    }
    else if (state = 1){// wait for selection
        UI.check();
        if (UI.triggered){// on selection exit/ entrance to releasing marbles
            // stairclimb motor on
           
            // release marbles
            timerStartTime = millis(); // set the start of the countdown
            state = 2;
        }
    }
    else if (state = 2){// wait for marbles to fall out of gates
        // should put in some sort of timing control
        if (millis() - timerStartTime > 200){
            // release solenoids off
            endPlates.reset(); // get the end plates ready
            state = 3;
        }
    }
    else if (state = 3){ // running
        endPlates.check();
        if (endPlates.allThree){// on exit of running
            if (endPlates.firstPin = UI.firstPin){
                credits++; // you win!
            }
            // reset motor on
            // stairclimb motor off
            state = 4;
        }
    }
    else if (state = 4){// resetting
        if (digitalRead(distributerDonePin)){
             // stop resetting
             // reset motor off
            state = 0;
        }
    }
    else{
        // oh dear, uhhh...
        // print error here
        Serial.write("ERROR: Invalid state. returning to startup state\n");
        state = 0;
    }
}


int acceptPayment(){
    // insert the part of payment accepting that runs every cycle
}


