

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