#pragma once
#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int basearmA_pos = 90, forearm_pos = 90, hand_pos = 90, gripperTurner_pos = 90, gripperOpener_pos = 90;
int basearmA_pos_temp = 90, forearm_pos_temp = 90, hand_pos_temp = 90, gripperTurner_pos_temp = 90, gripperOpener_pos_temp = 90;
string servos_command;
int servos_value = 90;

void CreateServoSliders()
{
	createTrackbar("Basearm", "Claw", &basearmA_pos_temp, 180);
	createTrackbar("Forearm", "Claw", &forearm_pos_temp, 180);
	createTrackbar("Hand", "Claw", &hand_pos_temp, 180);
	createTrackbar("Turner", "Claw", &gripperTurner_pos_temp, 180);
	createTrackbar("Opener", "Claw", &gripperOpener_pos_temp, 180);
}

void UpdateServosInput()
{
	if (basearmA_pos_temp != basearmA_pos)
	{
		basearmA_pos = basearmA_pos_temp;
		servos_command = "MoveBasearm";
		servos_value = basearmA_pos;
	}
	else if (forearm_pos_temp != forearm_pos)
	{
		forearm_pos = forearm_pos_temp;
		servos_command = "MoveForearm";
		servos_value = forearm_pos;
	}
	else if (hand_pos_temp != hand_pos)
	{
		hand_pos = hand_pos_temp;
		servos_command = "MoveHand";
		servos_value = hand_pos;
	}
	else if (gripperTurner_pos_temp != gripperTurner_pos)
	{
		gripperTurner_pos = gripperTurner_pos_temp;
		servos_command = "MoveGripperTurner";
		servos_value = gripperTurner_pos;
	}
	else if (gripperOpener_pos_temp != gripperOpener_pos)
	{
		gripperOpener_pos = gripperOpener_pos_temp;
		servos_command = "MoveGripperOpener";
		servos_value = gripperOpener_pos;
	}
	else {
		servos_command = "";
		servos_value = 90;
	}
}