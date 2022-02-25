#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32MultiArray.h>
#include "Sensors.h"
#include "Motors.h"

String current_command = "";
int current_value = 0;
std_msgs::UInt16 gas;
std_msgs::Float32MultiArray temperature;
void commandCallback(std_msgs::String& command){
  current_command = command.data;
}
void valueCallback(std_msgs::UInt16& value){
  current_value = value.data;
}
ros::NodeHandle nodehandle;
ros::Publisher pub_temperature("temperature", &temperature);
ros::Publisher pub_gas("gas", &gas);
ros::Subscriber<std_msgs::String> sub_command("arduino_command", &commandCallback);
ros::Subscriber<std_msgs::UInt16> sub_value("arduino_value", &valueCallback);

void ControlMotors(String command, int command_parameter) {
  if (command == "MoveBasearm"){
    MoveServo(0, command_parameter);
  } else if (command == "MoveForearm"){
    MoveServo(1, command_parameter);
  } else if (command == "MoveHand"){
    MoveServo(2, command_parameter);
  } else if (command == "MoveGripperTurner"){
    MoveServo(3, command_parameter);
  } else if (command == "MoveGripperOpener"){
    MoveServo(4, command_parameter);
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
  MotorsInitialize();
  nodehandle.initNode();
  nodehandle.advertise(pub_temperature);
  nodehandle.advertise(pub_gas);
  nodehandle.subscribe(sub_command);
  nodehandle.subscribe(sub_value);
}

void loop() {
  ReadSensors();
  temperature.data_length = AMG88xx_PIXEL_ARRAY_SIZE;
  memcpy(temperature.data, amg88_pixels, sizeof(amg88_pixels));
  gas.data = CO2level;
  pub_temperature.publish(&temperature);
  pub_gas.publish(&gas);
  nodehandle.spinOnce();
  ControlMotors(current_command, current_value);
}
