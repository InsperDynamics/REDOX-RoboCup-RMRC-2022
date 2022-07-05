#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
float current_temperature[64] = {0};
int current_gas = 0;
float cmdvel_linear_x = 0;
float cmdvel_angular_z = 0;
std_msgs::String arduino_command;
std_msgs::UInt16 arduino_value_1;
std_msgs::UInt16 arduino_value_2;
ros::Publisher pub_command;
ros::Publisher pub_value_1;
ros::Publisher pub_value_2;
ros::Subscriber sub_temperature;
ros::Subscriber sub_gas;
ros::Subscriber sub_cmdvel;

void temperatureCallback(const std_msgs::Float32MultiArray& temperature)
{
	for (int i=0; i < 64; i++) {
    	current_temperature[i] = temperature.data[i];
  	}
}

void gasCallback(const std_msgs::UInt16& gas)
{
	current_gas = gas.data;
}

void cmdvelCallback(const geometry_msgs::Twist& cmdvel)
{
	cmdvel_linear_x = cmdvel.linear.x;
	cmdvel_angular_z = cmdvel.angular.z;
}

void ConnectROS(int argc, char** argv)
{
	system("gnome-terminal -- roscore");
	sleep_for(seconds(10));
	system("gnome-terminal -- sudo chmod a+rw /dev/ttyACM0 ; cd ~/catkin_ws ; chmod 0777 src/ydlidar_ros_driver/startup/* ; sudo sh src/ydlidar_ros_driver/startup/initenv.sh");
	sleep_for(seconds(10));
	system("gnome-terminal -- rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=115200");
	ros::init(argc, argv, "redox_main");
	ros::NodeHandle nodehandle;
	pub_command = nodehandle.advertise<std_msgs::String>("arduino_command", 1000);
	pub_value_1 = nodehandle.advertise<std_msgs::UInt16>("arduino_value_1", 1000);
	pub_value_2 = nodehandle.advertise<std_msgs::UInt16>("arduino_value_2", 1000);
	sub_temperature = nodehandle.subscribe("temperature", 1000, &temperatureCallback);
	sub_gas = nodehandle.subscribe("gas", 1000, &gasCallback);
	sub_cmdvel = nodehandle.subscribe("cmd_vel", 1000, &cmdvelCallback);
	system("gnome-terminal -- roslaunch REDOX redox.launch");
}

void ReadArduino() 
{
	ros::spinOnce();
	sleep_for(microseconds(1000));
}

void WriteArduino(string command, int value_1, int value_2)
{
	arduino_command.data = command;
	arduino_value_1.data = value_1;
	arduino_value_2.data = value_2;
	pub_command.publish(arduino_command);
	pub_value_1.publish(arduino_value_1);
	pub_value_2.publish(arduino_value_2);
}