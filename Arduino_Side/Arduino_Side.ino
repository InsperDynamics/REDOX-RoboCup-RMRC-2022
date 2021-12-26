#include "Sensors.h"
#include "Motors.h"
String incoming_msg;

void ReadSerial() {
  incoming_msg = "";
  while (Serial.available()) {
    incoming_char = (char)Serial.read();
    if(incoming_char == '\n') {
      incoming_msg = "";
    }
    else {
      incoming_msg += incoming_char;
    }
  }
}

void WriteSerial() {
	for(int i=0; i<AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    	Serial.print(amg88_pixels[i]);
    	Serial.print(", ");
  }
	Serial.println(CO2level);
}

String splitstring(String str) {
  char splitted[sizeof(str)];
  String word = "";
  word_index = 0;
  for (auto c : str) {
      if (c == ' ') {
        splitted[word_index] = word;
        word_index++;
        word = "";
      }
      else {
        word += c;
      }
  }
  return splitted;
}

void ControlMotors(String splitted) {
  String command = splitted[0]
  int command_parameter = atoi(splitted[1]);
  switch(command) {
    case "RetractArm":
      RetractArm();
      break;
    case "ExtendArm":
      ExtendArm();
      break;
    case "MoveBasearmA":
      MoveBasearmA(command_parameter);
      break;
    case "MoveBasearmB":
      MoveBasearmB(command_parameter);
      break;
    case "MoveForearm":
      MoveForearm(command_parameter);
      break;
    case "MoveHand":
      MoveHand(command_parameter);
      break;
    case "MoveGripperTurner":
      MoveGripperTurner(command_parameter);
      break;
    case "MoveGripperOpener":
      MoveGripperOpener(command_parameter);
      break;
    case "MotorsRelease":
      MotorsRelease();
      break;
    case "MotorsStop":
      MotorsStop();
      break;
    case "MoveForward":
      MoveForward(command_parameter);
      break;
    case "MoveBackwards":
      MoveBackwards(command_parameter);
      break;
    case "RotateLeft":
      RotateLeft(command_parameter);
      break;
    case "RotateRight":
      RotateRight(command_parameter);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  MotorsInitialize();
}

void loop() {
  ReadSerial();
  Serial.flush();
  ControlMotors(splitstring(incoming_msg));
  ReadSensors();
  WriteSerial();
}