#pragma once
#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int basearmA_pos = 90, forearm_pos = 90, hand_pos = 90, gripperTurner_pos = 90, gripperOpener_pos = 90;
int basearmA_pos_temp = 90, forearm_pos_temp = 90, hand_pos_temp = 90, gripperTurner_pos_temp = 90, gripperOpener_pos_temp = 90;

void CreateServoSliders()
{
	createTrackbar("Basearm", "Claw", &basearmA_pos_temp, 180);
	createTrackbar("Forearm", "Claw", &forearm_pos_temp, 180);
	createTrackbar("Hand", "Claw", &hand_pos_temp, 180);
	createTrackbar("Turner", "Claw", &gripperTurner_pos_temp, 180);
	createTrackbar("Opener", "Claw", &gripperOpener_pos_temp, 180);
}

string CheckServoCommand()
{
	if (basearmA_pos_temp != basearmA_pos)
	{
		basearmA_pos = basearmA_pos_temp;
		return "MoveBasearm," + to_string(basearmA_pos) + "\n";
	}
	else if (forearm_pos_temp != forearm_pos)
	{
		forearm_pos = forearm_pos_temp;
		return "MoveForearm," + to_string(forearm_pos) + "\n";
	}
	else if (hand_pos_temp != hand_pos)
	{
		hand_pos = hand_pos_temp;
		return "MoveHand," + to_string(hand_pos) + "\n";
	}
	else if (gripperTurner_pos_temp != gripperTurner_pos)
	{
		gripperTurner_pos = gripperTurner_pos_temp;
		return "MoveGripperTurner," + to_string(gripperTurner_pos) + "\n";
	}
	else if (gripperOpener_pos_temp != gripperOpener_pos)
	{
		gripperOpener_pos = gripperOpener_pos_temp;
		return "MoveGripperOpener," + to_string(gripperOpener_pos) + "\n";
	}
	return "";
}