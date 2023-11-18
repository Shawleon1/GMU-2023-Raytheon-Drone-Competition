#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int16MultiArray.h>

ros::NodeHandle nodeHandle;
const int minSteering = 1000;
const int maxSteering = 2000;
const int brk_delay = 500;


int servo_values[6];

unsigned long last_msg_time = 0;
unsigned long brk_timer;
bool prev_dir;

float Throttle_cmd;
float smt_Throttle;

Servo steeringServo;

float fmap(float toMap, float in_min, float in_max, float out_min, float out_max) {
  return (toMap - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float fw_to_rev(float th){
  if (brk_timer == 0){
    brk_timer = millis();
  }

  if((millis() - brk_timer) < brk_delay ){
    return th;
  }
  else{

    if((millis() - brk_timer) < (brk_delay + 200)){
      return 0.0;
    }
    else{
      brk_timer = 0;
      prev_dir = 1;
      return th;
    }

  }
}

float rev_to_fw(){
  if (brk_timer == 0){
    brk_timer = millis();
  }

  if((millis() - brk_timer) < (brk_delay + 100) ){
    return 0.0;
  }
  else{
      brk_timer = 0;
      prev_dir = 0;
      return 0.0;
  }

}

void driveCallback( const std_msgs::Float32MultiArray&  control_msg ){
  //timestamp the  last ros message
  last_msg_time = millis();

  //Handle for steering command
  //Map steering command to servo output
  float steer_cmd = fmap(control_msg.data[0], -1.0, 1.0, minSteering, maxSteering);
  if (steer_cmd < minSteering) {
    steer_cmd = minSteering;
  }
  if (steer_cmd > maxSteering) {
    steer_cmd = maxSteering ;
  }
  //write Servo output for steering
  servo_values[0] = steer_cmd;

  //Handle for throttle command
  if ((control_msg.data[1] == 0)){
    Throttle_cmd = 0;
    smt_Throttle = 0;
  }
  // ESC forward continue
  if ((control_msg.data[1] >= 0) && (prev_dir == 0)){
    Throttle_cmd = control_msg.data[1];
    smt_Throttle = smt_Throttle + 0.2 * (Throttle_cmd - smt_Throttle);
  }
  
  //ESC reverse continue 
  if ((control_msg.data[1] < 0 ) && (prev_dir == 1)){
    Throttle_cmd = control_msg.data[1];
    smt_Throttle = smt_Throttle + 0.2 * (Throttle_cmd - smt_Throttle);
  }

  //From forward to rev
  if ((control_msg.data[1] < 0 ) && (prev_dir == 0)){
    Throttle_cmd = fw_to_rev(control_msg.data[1]);
    smt_Throttle = Throttle_cmd;
  }

  //From rev to forward
  if ((control_msg.data[1] > 0 ) && (prev_dir == 1)){ 
    Throttle_cmd = rev_to_fw();
    smt_Throttle = Throttle_cmd;
  }

}

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

//Control message subscriber
ros::Subscriber<std_msgs::Float32MultiArray> driveSubscriber("/cmd_vel1", &driveCallback);

//rpmVal_data Publisher for sensor readings
std_msgs::Int16MultiArray rpmVal;
ros::Publisher rpmVal_data("rpmVal_data", &rpmVal);

//optiFlow_data Publisher for sensor readings
std_msgs::Int16MultiArray optiFlow;
ros::Publisher optiFlow_data("optiFlow_data", &optiFlow);


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

