#include "Arduino.h"
#include "MotorGB.h"  

/* l MOTOR */
int l_MotorPinA;
int l_MotorPinB; 
int off_pulseWidth_l;// input
int on_pulseWidth_l;// input
volatile uint16_t count_l = 0;
int pulse_l = 0;
int direction_l;// input
volatile uint16_t A_pulse_count_l=0;
volatile uint16_t B_pulse_count_l=0;
int Status_l=0;

/* r MOTOR */
int r_MotorPinA;
int r_MotorPinB; 
int off_pulseWidth_r; // input, delay
int on_pulseWidth_r; // input, step angle
volatile uint16_t count_r = 0;
int pulse_r = 0;
int direction_r; // direction,input
volatile uint16_t A_pulse_count_r=0;
volatile uint16_t B_pulse_count_r=0;
int Status_r=0;

MotorGB::MotorGB() {
    setupTimer();
    sei(); 
}

void setupTimer() {
  TCCR1A = 0x00; 
  TCCR1B = 0x00; 
  TCCR1B |= (1 << WGM12) | (1 << CS11); // Set WGM12 and CS12 bits (Prescaler=8)
  TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); // Enable Timer1 Compare Match A and B interrupts
  OCR1A = 65500; // period frequency (30hz) 
  OCR1B = 1; // on frequency (2Mhz)
}

void MotorGB::attachA(int motorPin_one,int motorPin_two) { 
  ::l_MotorPinA = motorPin_one;
  ::l_MotorPinB = motorPin_two;
  pinMode(l_MotorPinA, OUTPUT);
  pinMode(l_MotorPinB, OUTPUT);
}

void MotorGB::attachB(int motorPin_one,int motorPin_two) { 
  ::r_MotorPinA = motorPin_one;
  ::r_MotorPinB = motorPin_two;
  pinMode(r_MotorPinA, OUTPUT);
  pinMode(r_MotorPinB, OUTPUT);
}

ISR(TIMER1_COMPA_vect) { 
  count_l++;  // period count: on_pulsewidth + off_pulsewidth
  count_r++;  // period count: on_pulsewidth + off_pulsewidth
}

ISR(TIMER1_COMPB_vect) { 
//////////////////////////////////////////////////////////////////////////////////////////
/*l MOTOR*/
//////////////////////////////////////////////////////////////////////////////////////////
/* A DIRECTION */
   if (count_l < on_pulseWidth_l && direction_l == 1) {
  digitalWrite(l_MotorPinA, HIGH);
}
/* B DIRECTION */
    if (count_l < on_pulseWidth_l && direction_l == 0) {
  digitalWrite(l_MotorPinA, HIGH);
} 

if (count_l >= on_pulseWidth_l ) {
     digitalWrite(l_MotorPinA, LOW);
    digitalWrite(l_MotorPinB, LOW);
    pulse_l++;// off count
    if (pulse_l > off_pulseWidth_l) {
      count_l = 0; // Reset count for the next period
      pulse_l = 0;
      A_pulse_count_l++;//count the number of period
    }
  }

/////////////////////////////////////////////////////////////////////////////////////////////////
/*r MOTOR*/
/////////////////////////////////////////////////////////////////////////////////////////////////
/* A DIRECTION */
   if (count_r < on_pulseWidth_r && direction_r == 1) {
   digitalWrite(r_MotorPinA, HIGH);
}
/* B DIRECTION */
    if (count_r < on_pulseWidth_r && direction_r == 0) {
    digitalWrite(r_MotorPinB, HIGH);
}

if (count_r >= on_pulseWidth_r ) {
     digitalWrite(r_MotorPinA, LOW);
    digitalWrite(r_MotorPinB, LOW);
    pulse_r++;// off count
    if (pulse_r > off_pulseWidth_r) {
      count_r = 0; // Reset count for the next period
      pulse_r = 0;
      A_pulse_count_r++;//count the number of period
    }
  }
}

void MotorGB::writeA(int on_dur, int off_dur, int dir) {
  ::on_pulseWidth_l = on_dur;
  ::off_pulseWidth_l = off_dur;
  ::direction_l = dir;
}

void MotorGB::writeB(int on_dur, int off_dur, int dir) {
  ::on_pulseWidth_r = on_dur;
  ::off_pulseWidth_r = off_dur;
  ::direction_r = dir;
}

uint16_t MotorGB::readA(){
   if (Status_l > off_pulseWidth_l || Status_l < off_pulseWidth_l) {
        Status_l=off_pulseWidth_l;//save the current pulsewidth
        A_pulse_count_l=0;
    }
    return A_pulse_count_l;//number of on periods
}

uint16_t MotorGB::readB(){
     if (Status_l > off_pulseWidth_r || Status_l < off_pulseWidth_r) {
        Status_l=off_pulseWidth_r;//save the current pulsewidth
        A_pulse_count_r=0;
    }
    return B_pulse_count_r;//number of on periods
}