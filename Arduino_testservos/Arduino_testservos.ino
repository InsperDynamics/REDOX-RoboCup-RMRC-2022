#include <Servo.h>
#define basearmA_pin 2
#define basearmB_pin 7
#define forearm_pin 4
#define hand_pin 5
#define gripperTurner_pin 3
#define gripperOpener_pin 6
Servo basearmA, basearmB, forearm, hand, gripperTurner, gripperOpener;

void setup() {
  basearmA.attach(basearmA_pin);
  //basearmB.attach(basearmB_pin);
  //forearm.attach(forearm_pin);
  //hand.attach(hand_pin);
  //gripperOpener.attach(gripperOpener_pin);
  //gripperTurner.attach(gripperTurner_pin);
}

void loop() {
  basearmA.write(90);
}
