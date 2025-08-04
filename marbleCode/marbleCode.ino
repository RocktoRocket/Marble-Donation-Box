#include <arduino.h>
#include "buttons.h"
#include "payment.h"

// C++ code
//

// placeholder pin numbers change these please
constexpr int readyPin = 13; // saving pinout numbers for later
constexpr int runningPin = 12; // these three are for testing purposes
constexpr int readyingPin = 7;

constexpr int endgate1 = 8;
constexpr int endgate2 = 6;
constexpr int endgate3 = 5;

constexpr int redButton1 = 4;
constexpr int redButton2 = 3;
constexpr int redButton3 = 2;

constexpr int buttonLight1 = 9;
constexpr int buttonLight2 = 10;
constexpr int buttonLight3 = 11;


constexpr int distributerDonePin = 23; // the limit switch on the third distributer section
constexpr int marbleRelease = 24;
constexpr int distributerReset = 25;
constexpr int augerMotor = 26;
constexpr int stairMotor = 27;
constexpr int gyroMotor = 28;

// function declarations to avoid possible future problems
void doStates(int &state, int &credits, ButtonInterface &UI, ButtonInterface &endPlates);

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
            Serial.write("payment recived\n");
            credits--;
           
            state = 1;
        }
    }
    else if (state = 1){// wait for selection
        UI.check();
        if (UI.triggered){// on selection exit/ entrance to releasing marbles

            Serial.write("path selected\n");

            digitalWrite(stairMotor, HIGH);// stairclimb motor on

           
            digitalWrite(marbleRelease, HIGH);// release marbles
            timerStartTime = millis(); // set the start of the countdown
            state = 2;
        }
    }
    else if (state = 2){// wait for marbles to fall out of gates
        // should put in some sort of timing control
        if (millis() - timerStartTime > 200){
            digitalWrite(marbleRelease, LOW);// release solenoids off
            endPlates.reset(); // get the end plates ready
            state = 3;
        }
    }
    else if (state = 3){ // running
        endPlates.check();
        if (endPlates.allThree){// on exit of running
            Serial.write("done running\n");
            if (endPlates.firstPin = UI.firstPin){
                Serial.write("you win\n");
                credits++; // you win!
            }
            digitalWrite(augerMotor, HIGH);// reset motor on
            digitalWrite(stairclimb, LOW);// stairclimb motor off
            state = 4;
        }
    }
    else if (state = 4){// resetting
        if (digitalRead(distributerDonePin)){
            Serial.write("done reseting\n");
             // stop resetting
            digitalWrite(augerMotor, LOW); // reset motor off
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


