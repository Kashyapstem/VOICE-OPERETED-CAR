/* voice control car */


#include <SoftwareSerial.h>
#include <EasyVR.h>


SoftwareSerial mySerial(0, 1); // RX, TX
EasyVR easyvr(mySerial);




int motor1PWM = 5;  // PWM control for Motor 1 (enable pin 1 of L293d IC)
int motor1frwd_right = 4; // Direction control 1 for Motor 1
int motor1bckwrd_right = 7; // Direction control 2 for Motor 1


int motor2PWM = 6;  // PWM control for Motor 2 (enable pin 2 of L293d IC)
int motor1frwd_left = 8; // Direction control 1 for Motor 2
int motor1bckwrd_left = 9; // Direction control 2 for Motor 2


void setup()
{
  pinMode(motor1PWM, OUTPUT);
  pinMode(motor1frwd_right, OUTPUT);
  pinMode(motor1bckwrd_right, OUTPUT);


  pinMode(motor2PWM, OUTPUT);
  pinMode(motor1frwd_left, OUTPUT);
  pinMode(motor1bckwrd_left, OUTPUT);


  // Initialize serial communication with EasyVR
  mySerial.begin(9600);
  easyvr.setTimeout(500);
}


void loop() {
  if (easyvr.detect() == EasyVR::TRIGGER) {
    int16_t id = easyvr.getID();
    executeCommand(id);
  }
}


void executeCommand(int16_t command) {
  switch (command) {
    case 1: // Voice command: "Forward"
      moveForward();
      break;
    case 2: // Voice command: "Backward"
      moveBackward();
      break;
    case 3: // Voice command: "Left"
      turnLeft();
      break;
    case 4: // Voice command: "Right"
      turnRight();
      break;
    case 5: // Voice command: "Stop"
      stopMotors();
      break;
    // Add more cases for additional voice commands
  }
}




void moveForward() {
  digitalWrite(motor1frwd_right, HIGH);
  digitalWrite(motor1bckwrd_right, LOW);
  analogWrite(motor1PWM, 255);


  digitalWrite(motor1frwd_left, HIGH);
  digitalWrite(motor1bckwrd_left, LOW);
  analogWrite(motor2PWM, 255);
}


void moveBackward() {
  digitalWrite(motor1frwd_right, LOW);
  digitalWrite(motor1bckwrd_right, HIGH);
  analogWrite(motor1PWM, 255);


  digitalWrite(motor1frwd_left, LOW);
  digitalWrite(motor1bckwrd_left, HIGH);
  analogWrite(motor2PWM, 255);
}


void turnLeft() {
  digitalWrite(motor1frwd_right, LOW);
  digitalWrite(motor1bckwrd_right, HIGH);
  analogWrite(motor1PWM, 200);


  digitalWrite(motor1frwd_left, HIGH);
  digitalWrite(motor1bckwrd_left, LOW);
  analogWrite(motor2PWM, 200);
}


void turnRight() {
  digitalWrite(motor1frwd_right, HIGH);
  digitalWrite(motor1bckwrd_right, LOW);
  analogWrite(motor1PWM, 200);


  digitalWrite(motor1frwd_left, LOW);
  digitalWrite(motor1bckwrd_left, HIGH);
  analogWrite(motor2PWM, 200);
}


void stopMotors() {
  digitalWrite(motor1frwd_right, LOW);
  digitalWrite(motor1bckwrd_right, LOW);
  analogWrite(motor1PWM, 0);


  digitalWrite(motor1frwd_left, LOW);
  digitalWrite(motor1bckwrd_left, LOW);
  analogWrite(motor2PWM, 0);
}
