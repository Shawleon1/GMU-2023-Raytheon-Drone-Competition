#include <Servo.h>

Servo steeringServo;
/*
const int steeringPin = 2;
const int drivePin = 3;


void setup() {
  pinMode(steeringPin, OUTPUT);
  pinMode(drivePin, OUTPUT);
}

*/
// static const int THROTTLE_IN = 5;
// static const int STEERING_IN = 2;

// static const int THROTTLE_OUT = 9;
static const int STEERING_OUT = 2;
float servoval = 500.0;
static const int NUM_CHANNELS = 1;
// static const int PWM_IN_DISCONNECT = 700;
// static const int PWM_OUT_DISCONNECT = 1500;

// // float channel[NUM_CHANNELS];
// int button = 1;

void setup() {
  // put your setup code here, to run once:
  steeringServo.attach(STEERING_OUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    servoval = Serial.parseFloat();
    while(Serial.read() == '\n');
    Serial.print("input value");
    Serial.println(servoval);
    delay(500);
    servoval = servoval * 1000;
    Serial.print("multiply value");
    Serial.println(servoval);
    delay(500);
    servoval = servoval + 1000;
  }
  Serial.println(servoval);

  steeringServo.writeMicroseconds(servoval);
  delay(500);
}

