#include <MotorGB.h>

// Define motor pins
const int motorAPin1 = 3;
const int motorAPin2 = 5;
const int motorBPin1 = 6;
const int motorBPin2 = 10;

// Create MotorGB instances
MotorGB motor;

void setup() {
  // Attach motor pins
  motor.attachA(motorAPin1, motorAPin2);
  motor.attachB(motorBPin1, motorBPin2);
  Serial.begin(9600);

  // Set motor parameters
  motor.writeB(10, 10, 1); // On duration: 10us, Off duration: 10us, Direction: 1
  motor.writeA(10, 10, 1); // On duration: 10us, Off duration: 10us, Direction: 1
}

void loop() {
  // Read motor A and B pulse counts
  uint16_t pulseCountA = motor.readA();
  uint16_t pulseCountB = motor.readB();


  // Print pulse counts
  Serial.print("Motor A pulse count: ");
  Serial.println(pulseCountA);
  Serial.print("Motor B pulse count: ");
  Serial.println(pulseCountB);


  // Delay before next reading
  delay(1000);
}
