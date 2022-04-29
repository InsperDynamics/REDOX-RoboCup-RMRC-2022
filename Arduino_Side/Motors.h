#include <Servo.h> 
#define enableA 27
#define enableB 29
#define enableC 46
#define enableD 48
#define motorUR 10
#define motorURdirA 36
#define motorURdirB 32
#define motorLR 8
#define motorLRdirA 38
#define motorLRdirB 44
#define motorUL 11
#define motorULdirA 30
#define motorULdirB 34
#define motorLL 9
#define motorLLdirA 42
#define motorLLdirB 40
#define basearmA_pin 2
#define basearmB_pin 3
#define forearm_pin 7
#define hand_pin 4
#define gripperTurner_pin 5
#define gripperOpener_pin 6
Servo basearmA, basearmB, forearm, hand, gripperTurner, gripperOpener;

void MoveServo(int servo, int pos){
  switch(servo){
    case 0:
      basearmA.write(constrain(pos, 0, 180));
      basearmB.write(constrain(180 - pos, 0, 180));
      break;
    case 1:
      forearm.write(constrain(pos, 0, 180));
      break;
    case 2:
      hand.write(constrain(pos, 0, 180));
      break;
    case 3:
      gripperTurner.write(constrain(pos, 0, 180));
      break;
    case 4:
      gripperOpener.write(constrain(pos, 0, 180));
      break;
  }
}

void MotorsRelease(){
  digitalWrite(motorULdirA, LOW);
  digitalWrite(motorULdirB, LOW);
  digitalWrite(motorURdirA, LOW);
  digitalWrite(motorURdirB, LOW);
  digitalWrite(motorLLdirA, LOW);
  digitalWrite(motorLLdirB, LOW);
  digitalWrite(motorLRdirA, LOW);
  digitalWrite(motorLRdirB, LOW);
}
void MotorsStop(){
  digitalWrite(motorULdirA, HIGH);
  digitalWrite(motorULdirB, HIGH);
  digitalWrite(motorURdirA, HIGH);
  digitalWrite(motorURdirB, HIGH);
  digitalWrite(motorLLdirA, HIGH);
  digitalWrite(motorLLdirB, HIGH);
  digitalWrite(motorLRdirA, HIGH);
  digitalWrite(motorLRdirB, HIGH);
}

void MotorsInitialize(){
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(enableC, OUTPUT);
  pinMode(enableD, OUTPUT);
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(enableC, HIGH);
  digitalWrite(enableD, HIGH);
  pinMode(motorUL, OUTPUT);
  pinMode(motorULdirA, OUTPUT);
  pinMode(motorULdirB, OUTPUT);
  pinMode(motorUR, OUTPUT);
  pinMode(motorURdirA, OUTPUT);
  pinMode(motorURdirB, OUTPUT);
  pinMode(motorLL, OUTPUT);
  pinMode(motorLLdirA, OUTPUT);
  pinMode(motorLLdirB, OUTPUT);
  pinMode(motorLR, OUTPUT);
  pinMode(motorLRdirA, OUTPUT);
  pinMode(motorLRdirB, OUTPUT);
  basearmA.attach(basearmA_pin);
  basearmB.attach(basearmB_pin);
  forearm.attach(forearm_pin);
  hand.attach(hand_pin);
  gripperOpener.attach(gripperOpener_pin);
  gripperTurner.attach(gripperTurner_pin);
  MotorsRelease();
  basearmA.write(90);
  basearmB.write(90);
  forearm.write(90);
  hand.write(90);
  gripperTurner.write(90);
  gripperOpener.write(90);
}

void URForward(){
  digitalWrite(motorURdirA, HIGH);
  digitalWrite(motorURdirB, LOW);
}
void URBackwards(){
  digitalWrite(motorURdirA, LOW);
  digitalWrite(motorURdirB, HIGH);
}
void ULForward(){
  digitalWrite(motorULdirA, HIGH);
  digitalWrite(motorULdirB, LOW);
}
void ULBackwards(){
  digitalWrite(motorULdirA, LOW);
  digitalWrite(motorULdirB, HIGH);
}
void LRForward(){
  digitalWrite(motorLRdirA, HIGH);
  digitalWrite(motorLRdirB, LOW);
}
void LRBackwards(){
  digitalWrite(motorLRdirA, LOW);
  digitalWrite(motorLRdirB, HIGH);
}
void LLForward(){
  digitalWrite(motorLLdirA, HIGH);
  digitalWrite(motorLLdirB, LOW);
}
void LLBackwards(){
  digitalWrite(motorLLdirA, LOW);
  digitalWrite(motorLLdirB, HIGH);
}

void MoveForward(int speed){
  ULForward();
  LLForward();
  URForward();
  LRForward();
  analogWrite(motorUL, constrain(speed, 0, 250));
  analogWrite(motorLL, constrain(speed, 0, 250));
  analogWrite(motorUR, constrain(speed, 0, 250));
  analogWrite(motorLR, constrain(speed, 0, 250));
}
void MoveBackwards(int speed){
  ULBackwards();
  LLBackwards();
  URBackwards();
  LRBackwards();
  analogWrite(motorUL, constrain(speed, 0, 250));
  analogWrite(motorLL, constrain(speed, 0, 250));
  analogWrite(motorUR, constrain(speed, 0, 250));
  analogWrite(motorLR, constrain(speed, 0, 250));
}
void RotateLeft(int speed){
  ULBackwards();
  LLBackwards();
  URForward();
  LRForward();
  analogWrite(motorUL, constrain(speed, 0, 250));
  analogWrite(motorLL, constrain(speed, 0, 250));
  analogWrite(motorUR, constrain(speed, 0, 250));
  analogWrite(motorLR, constrain(speed, 0, 250));
}
void RotateRight(int speed){
  ULForward();
  LLForward();
  URBackwards();
  LRBackwards();
  analogWrite(motorUL, constrain(speed, 0, 250));
  analogWrite(motorLL, constrain(speed, 0, 250));
  analogWrite(motorUR, constrain(speed, 0, 250));
  analogWrite(motorLR, constrain(speed, 0, 250));
}
