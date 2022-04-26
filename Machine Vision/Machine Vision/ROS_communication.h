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
ros::Publisher pub_command;
ros::Publisher pub_value;
ros::Subscriber sub_temperature;
ros::Subscriber sub_gas;

void temperatureCallback(const std_msgs::Float32MultiArray& temperature) {
	memcpy(&current_temperature, &temperature.data, sizeof(temperature.data));
}

void gasCallback(const std_msgs::UInt16& gas) {
	current_gas = gas.data;
}

void ConnectROS(int argc, char** argv)
{
	ros::init(argc, argv, "redox_main");
	ros::NodeHandle nodehandle;
	pub_command = nodehandle.advertise<std_msgs::String>("arduino_command", 1000);
	pub_value = nodehandle.advertise<std_msgs::UInt16>("arduino_value", 1000);
	sub_temperature = nodehandle.subscribe("temperature", 1000, &temperatureCallback);
	sub_gas = nodehandle.subscribe("gas", 1000, &gasCallback);
	system("gnome-terminal -x bash -c 'roslaunch ../../catkin_ws/redox_autonomous.launch'");
}

void ReadArduino() 
{
	ros::spinOnce();
}

void WriteArduino(string command, int value)
{
	arduino_command.data = command;
	arduino_value.data = value;
	pub_command.publish(arduino_command);
	pub_value.publish(arduino_value);
}