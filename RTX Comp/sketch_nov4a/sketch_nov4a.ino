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
static const int THROTTLE_IN = 5;
static const int STEERING_IN = 6;

static const int THROTTLE_OUT = 9;
static const int STEERING_OUT = 10;

static const int NUM_CHANNELS = 2;
static const int PWM_IN_DISCONNECT = 700;
static const int PWM_OUT_DISCONNECT = 1500;

float channel[NUM_CHANNELS];
int button = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(THROTTLE_OUT, OUTPUT);
  pinMode(STEERING_OUT, OUTPUT);

  pinMode(THROTTLE_IN, INPUT);
  pinMode(THROTTLE_IN, INPUT);
  pinMode(button, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  channel[0] = pulseIn(THROTTLE_IN, HIGH);
  channel[1] = pulseIn(STEERING_IN, HIGH);
  
  int pulse;

  if(input < 0 && input >= -1){
    pulse = 1000;
    pulse += 500 * (input * -1);

  }

  if(input >= 0 && input <= 1){
    pulse = 1500;
    pulse += 500 * (input * -1);
  }

  digitalWrite(THROTTLE_OUT, LOW);
  delay(pulse);
  digitalWrite(THROTTLE_OUT,HIGH);
  delay(pulse);

}
