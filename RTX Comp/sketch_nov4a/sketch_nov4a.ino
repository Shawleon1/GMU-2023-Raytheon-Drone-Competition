int led = 13;
int input = -1;
int button = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(button, INPUT;

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
