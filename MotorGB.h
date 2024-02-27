#ifndef MotorGB_h
#define MotorGB_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class MotorGB {
public:
    MotorGB(); // Constructor declaration
    void attachA(int pin_one,int pin_two); // Method declaration
    void attachB(int pin_one,int pin_two); // Method declaration
    void writeA(int on_dur, int off_dur, int dir); // write the duration of an on/off pulse in mircoseconds and directions (1/0). on duration determines the step angle while off duration determines the speed. 
    void writeB(int on_dur, int off_dur, int dir); // write the duration of an on/off pulse in mircoseconds and directions (1/0). on duration determines the step angle while off duration determines the speed. 
    uint16_t readA(); // read the number of period or step angle of an active on pulse.
    uint16_t readB(); // read the number of period or step angle of an active on pulse.
private:
    // private members 
};

#endif