# MotorGB Library

## Introduction
The MotorGB library is designed to control DC motors with an Arduino board. It facilitates precise control over motor speed and direction using pulse-width modulation (PWM) signals. By adjusting the duration of the on and off pulses, users can control both the speed and direction of the motors.

## Circuit
To use the MotorGB library, you'll need to connect the DC motor to the Arduino board. Connect the positive terminal of the motor to a digital pin on the Arduino (referred to as MotorPinA), and the negative terminal to another digital pin (MotorPinB). Additionally, connect the ground of the Arduino to the ground of the motor's power supply.

## Methodology
The MotorGB library utilizes pulse-width modulation (PWM) signals to control the speed and direction of the DC motor. PWM is achieved by rapidly toggling the output pin between HIGH and LOW states at a specific frequency.

The library uses Timer1 of the Arduino to generate the PWM signal. Timer1 is configured to generate an interrupt at a predefined frequency (30Hz) using the setupTimer() function. This interrupt triggers the ISR(TIMER1_COMPA_vect) and ISR(TIMER1_COMPB_vect) functions, which handle the generation of PWM signals for two motors independently.

Inside the ISR functions, the library checks the count of the on and off pulses for each motor. Based on the direction and pulse width settings provided by the user, it toggles the output pins accordingly to generate the desired PWM signal.

## Methods
- `attachA(int pin_one, int pin_two)`: This method is used to attach the DC motor to the specified Arduino pins for one-direction control.

pin_one: The digital pin connected to one terminal of the DC motor.
pin_two: The digital pin connected to the other terminal of the DC motor.

- `attachB(int pin_one, int pin_two)`:  Similar to attachA, this method attaches the DC motor to the specified Arduino pins for bi-directional control.

pin_one: The digital pin connected to one terminal of the DC motor.
pin_two: The digital pin connected to the other terminal of the DC motor.

- `writeA(int on_dur, int off_dur, int dir)`:Sets the duration of on and off pulses, as well as the direction of rotation for one-direction control.

on_dur: The duration of the on pulse in microseconds. This parameter determines the step angle of the motor.
off_dur: The duration of the off pulse in microseconds. This parameter determines the speed of the motor.
dir: The direction of rotation. Use 1 for forward rotation and 0 for reverse rotation.

- `writeB(int on_dur, int off_dur, int dir)`:  Similar to writeA, this method sets the duration of on and off pulses, as well as the direction of rotation for bi-directional control.

on_dur: The duration of the on pulse in microseconds. This parameter determines the step angle of the motor.
off_dur: The duration of the off pulse in microseconds. This parameter determines the speed of the motor.
dir: The direction of rotation. Use 1 for forward rotation and 0 for reverse rotation.

- `readA()`:  Reads the number of on periods for bi-direction control.

This method has no input parameters. It returns the number of on periods, providing information about the motor's operation.

- `readB()`:Reads the number of on periods for bi-directional control.

This method has no input parameters. It returns the number of on periods, providing information about the motor's operation.

## Conclusion (How to Use the Library)
To use the MotorGB library, follow these steps to install it from GitHub:
### Download the Library:
Visit the GitHub repository of the MotorGB library.
Click on the "Code" button and select "Download ZIP".
Extract the downloaded ZIP file.

### Installation:
Open the Arduino IDE.
Go to Sketch > Include Library > Add .ZIP Library.
Select the extracted folder of the MotorGB library and click "Open".
