#include <Servo.h> 
#define motorUR 8
#define motorURdirA 31
#define motorURdirB 33
#define motorLR 9
#define motorLRdirA 35
#define motorLRdirB 37
#define motorUL 10
#define motorULdirA 38
#define motorULdirB 51
#define motorLL 11
#define motorLLdirA 50
#define motorLLdirB 45
#define basearmA_pin 2
#define basearmB_pin 3
#define forearm_pin 4
#define hand_pin 5
#define gripperTurner_pin 6
#define gripperOpener_pin 7
Servo basearmA, basearmB, forearm, hand, gripperTurner, gripperOpener;

void RetractArm(){
	basearmA.write(90);
  basearmB.write(90);
  forearm.write(90);
  hand.write(90);
  gripperTurner.write(90);
  gripperOpener.write(90);
}
void ExtendArm(){
	basearmA.write(90);
  basearmB.write(90);
  forearm.write(90);
  hand.write(90);
  gripperTurner.write(90);
  gripperOpener.write(90);
}

void MoveBasearmA(int pos){
  basearmA.write(constrain(pos, 0, 180));
}
void MoveBasearmB(int pos){
  basearmB.write(constrain(pos, 0, 180));
}
void MoveForearm(int pos){
  forearm.write(constrain(pos, 0, 180));
}
void MoveHand(int pos){
  hand.write(constrain(pos, 0, 180));
}
void MoveGripperTurner(int pos){
  gripperTurner.write(constrain(pos, 0, 180));
}
void MoveGripperOpener(int pos){
  gripperOpener.write(constrain(pos, 0, 180));
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
  RetractArm();
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
