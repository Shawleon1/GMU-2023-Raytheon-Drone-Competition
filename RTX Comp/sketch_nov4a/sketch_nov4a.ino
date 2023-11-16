#include <Servo.h>
/*
Servo myservo;
const int steeringPin = 2;
const int drivePin = 3;


void setup() {
  pinMode(steeringPin, OUTPUT);
  pinMode(drivePin, OUTPUT);
}

*/


int led = 13;
float input = -1;
int button = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(button, INPUT;

}

void loop() {
  // put your main code here, to run repeatedly:
  int pulse;

  if(input < 0 && input >= -1){
    pulse = 1000;
    pulse += 500 * (input * -1);

  }

  if(input >= 0 && input <= 1){
    pulse = 1500;
    pulse += 500 * (input * -1);
  }

  digitalWrite(led, LOW);
  delay(pulse);
  digitalWrite(led,HIGH);
  delay(pulse);

}
