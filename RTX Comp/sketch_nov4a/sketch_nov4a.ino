#include <Servo.h>

Servo myservo;
const int steeringPin = 2;
const int drivePin = 3;


void setup() {
  pinMode(steeringPin, OUTPUT);
  pinMode(drivePin, OUTPUT);
}

void loop() {
  //wheel speed
  while (Serial.available() == 0) {
  }

  float wheelSpeed = Serial.parseFloat();
  
  //input 2
}


/*
int led = 10;
int input = -1;
int button = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pulse;

  if(input == -1){
    pulse = 1000;
  }

  if(input == 0){
    pulse = 1500;
  }

  if(input == 1){
    pulse = 2000;
  }

  digitalWrite(led, LOW);
  delay(pulse);
  digitalWrite(led,HIGH);
  delay(pulse);
}
*/