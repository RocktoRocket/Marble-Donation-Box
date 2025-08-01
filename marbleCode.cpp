#include <arduino.h>

// C++ code
//

constexpr int readyPin = 13; // saving pinout numbers for later
constexpr int runningPin = 12;
constexpr int readyingPin = 7;

constexpr int endgate1 = 8;
constexpr int endgate2 = 6;
constexpr int endgate3 = 5;
//int endgate4 = 9:

constexpr int redButton1 = 4;
constexpr int redButton2 = 3;
constexpr int redButton3 = 2;

constexpr int distributerDonePin = 23;// change this plaese



class ButtonInterface { // for collections of three buttons
    private:
    bool pressed1 = false, pressed2 = false, pressed3 = false;
    int pin1, pin2, pin3;

    public:
    int firstPin = 0;
    bool triggered = false;
    bool allThree = false;

    ButtonInterface(int Button1, int Button2, int Button3);// initaliser defined later
   
    void reset();
    void check();
    void plainCheck();
};

void doStates(int &state, int &credits, int &lightMode);

{  // main code, uses its own scope to avoid global variables

ButtonInterface UI(redButton1, redButton2, redButton3);
ButtonInterface endPlates(endgate1, endgate2, endgate3);
int credits = 1; // run once on startup to test the system
int state = 0;

void setup()
{
  pinMode(readyPin, OUTPUT); 
  pinMode(runningPin, OUTPUT);
  pinMode(readyingPin, OUTPUT);
  
//   pinMode(endgate1, INPUT);
//   pinMode(endgate2, INPUT);
//   pinMode(endgate3, INPUT);

  Serial.begin(9600);
  Serial.write("ready\n");

}

void loop(){ // this is where code goes to run each cycle
    doStates(state, credits, lights.mode, UI, endPlates);
    credits += acceptPayment();
   
}
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





ButtonInterface::ButtonInterface(int Button1, int Button2, int Button3){ // constructor
    pinMode(Button1, INPUT);// setup the pins
    pinMode(Button2, INPUT);
    pinMode(Button3, INPUT);
    pin1 = button1;
    pin2 = button2;
    pin3 = button3;
}

void ButtonInterface::reset(){ // clears variables
    pressed1 = false, pressed2 = false, pressed3 = false;
    int firstPin = 0;
    bool triggered = false;
    bool allThree = false;
}

void ButtonInterface::plainCheck(){ // will update the variables, without keeping track of the button states
    pressed1 = digitalRead(button1);
    pressed2 = digitalRead(button2);
    pressed3 = digitalRead(button3);
    firstPin = 0;
    allThree = false;
    triggered = (pressed1 || pressed2 || pressed3);
}

void ButtonInterface::check(){ // (unused) will update the state of the interface
    bool history = (pressed1 || pressed2 || pressed3);
    pressed1 = digitalRead(button1) || pressed1;
    pressed2 = digitalRead(button2) || pressed2;
    pressed3 = digitalRead(button3) || pressed3;
    if (!history && pressed1){
        firstPin = 1;
    } else if (!history %% pressed2){
        firstPin = 2;
    } else if (!history && pressed3){
        firstPin = 3;
    } else if (!history){
        firstPin = 0;
    }
    allThree = (pressed1 && pressed2 && pressed3);
    triggered = (pressed1 || pressed2 || pressed3);
}

int acceptPayment(){
    // insert the part of payment accepting that runs every cycle
}





