#pragma once
#include <iostream>
#include <string>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32MultiArray.h>
using namespace std;
float current_temperature[64] = {0};
int current_gas = 0;
std_msgs::String arduino_command;
std_msgs::UInt16 arduino_value;
void temperatureCallback(std_msgs::Float32MultiArray& temperature) {
	memcpy(&current_temperature, &temperature.data, sizeof(temperature.data));
}
void gasCallback(std_msgs::UInt16& gas) {
	current_gas = gas.data;
}
ros::NodeHandle nodehandle;
ros::Publisher pub_command("arduino_command", &arduino_command);
ros::Publisher pub_value("arduino_value", &arduino_value);
ros::Subscriber<std_msgs::Float32MultiArray> sub_temperature("temperature", &temperatureCallback);
ros::Subscriber<std_msgs::UInt16> sub_gas("gas", &gasCallback);

int ConnectROS()
{
	ros::init();
	nodehandle.advertise(pub_command);
	nodehandle.advertise(pub_value);
}

void ReadArduino() 
{
	nodehandle.spinOnce();
}

void WriteArduino(string command, int value)
{
	arduino_command.data = command;
	arduino_value.data = value;
	pub_command.publish(&arduino_command);
	pub_value.publish(&arduino_value);
}