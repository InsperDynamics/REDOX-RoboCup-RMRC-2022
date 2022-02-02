#include <Vector.h>
#include "Sensors.h"
#include "Motors.h"
String incoming_msg;
String outgoing_msg;

void ReadSerial() {
  incoming_msg = "";
  while (Serial.available()) {
    char incoming_char = (char)Serial.read();
    if(incoming_char == '\n' && Serial.available()) {
      incoming_msg = "";
    }
    else {
      incoming_msg += incoming_char;
    }
  }
}

void WriteSerial() {
  outgoing_msg = "";
	for(int i=0; i<AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    	outgoing_msg += String(amg88_pixels[i]);
    	outgoing_msg += ',';
  }
  outgoing_msg += String(CO2level);
	Serial.println(outgoing_msg);
}

Vector<String> splitstring(String str) {
  Vector<String> splitted;
  String word = "";
  int word_index = 0;
  for (auto c : str) {
    if (c == ',') {
      splitted.push_back(word);
      word_index++;
      word = "";
    }
    else {
      word += c;
    }
  }
  return splitted;
}

void ControlMotors(Vector<String> splitted) {
  String command = splitted[0];
  int command_parameter = 0;
  if (sizeof(splitted) > 1){
    int command_parameter = splitted[1].toInt();
  }
  if (command == "RetractArm"){
    RetractArm();
  } else if(command == "ExtendArm"){
    ExtendArm();
  } else if (command == "MoveBasearmForward"){
    MoveServo(0, command_parameter, 1);
  } else if (command == "MoveBasearmBackwards"){
    MoveServo(0, command_parameter, -1);
  } else if (command == "MoveForearmForward"){
    MoveServo(1, command_parameter, 1);
  } else if (command == "MoveForearmBackwards"){
    MoveServo(1, command_parameter, -1);
  } else if (command == "MoveHandForward"){
    MoveServo(2, command_parameter, 1);
  } else if (command == "MoveHandBackwards"){
    MoveServo(2, command_parameter, -1);
  } else if (command == "MoveGripperTurnerForward"){
    MoveServo(3, command_parameter, 1);
  } else if (command == "MoveGripperTurnerBackwards"){
    MoveServo(3, command_parameter, -1);
  } else if (command == "MoveGripperOpenerForward"){
    MoveServo(4, command_parameter, 1);
  } else if (command == "MoveGripperOpenerBackwards"){
    MoveServo(4, command_parameter, -1);
  } else if (command == "MotorsStop"){
    MotorsStop();
  } else if (command == "MotorsRelease"){
    MotorsRelease();
  } else if (command == "MoveForward"){
    MoveForward(command_parameter);
  } else if (command == "MoveBackwards"){
    MoveBackwards(command_parameter);
  } else if (command == "RotateLeft"){
    RotateLeft(command_parameter);
  } else if (command == "RotateRight"){
    RotateRight(command_parameter);
  }
}

void setup() {
  Serial.begin(115200);
  MotorsInitialize();
}

void loop() {
  ReadSerial();
  Vector<String> splitted = splitstring(incoming_msg);
  if (sizeof(splitted) >= 2){
    ControlMotors(splitted);
  }
  ReadSensors();
  WriteSerial();
  Serial.flush();
}
