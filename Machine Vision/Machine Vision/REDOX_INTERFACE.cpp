#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "ROS_communication.h"
#include "Gamepad_controller.h"
#include "Servos_controller.h"
#include "Mode_switcher.h"
#include "Thermal_gas.h"
#include "QR_read.h"
#include "Motion_detection.h"
#include "Hazmat_detection.h"
using namespace std;
using namespace cv;
int resolution_horizontal = 1920;
int resolution_vertical = 1080;
const int number_of_cameras = 4;
int current_camera_index = 0;
VideoCapture capture;
Mat webcam_image;

void checkUserInput()
{
	UpdateGamepadInput();
	UpdateServosInput();
	if (gamepad_command == "previous_camera")
	{
		current_camera_index--;
		if (current_camera_index < 0)
			current_camera_index = number_of_cameras - 1;
		capture.open(current_camera_index);
	}
	else if (gamepad_command == "next_camera")
	{
		current_camera_index++;
		if (current_camera_index > number_of_cameras - 1)
			current_camera_index = 0;
		capture.open(current_camera_index);
	}
	else if (!servos_command.empty() && !autonomous_movement)
	{
		cout << servos_command << "\n";
		WriteArduino(servos_command, servos_value, 0);
	}
	else if (!gamepad_command.empty() && !autonomous_movement)
	{
		cout << gamepad_command << " " << to_string(gamepad_value_1) << " " << to_string(gamepad_value_2) << "\n";
		WriteArduino(gamepad_command, gamepad_value_1, gamepad_value_2);
	}
}

void checkSensorsFeed()
{
	ReadArduino();
	UpdateGas(current_gas);
	UpdateThermal(current_temperature);
	capture >> webcam_image;
	if (qr_detection)
		webcam_image = ReadQR(webcam_image);
	if (hazmat_detection)
		webcam_image = DetectHazmat(webcam_image);
	if (motion_detection)
		webcam_image = DetectMotion(webcam_image);
}

void updateInterface()
{
	resizeWindow("REDOX", resolution_horizontal, resolution_vertical);
	copyMakeBorder(webcam_image, webcam_image, int((resolution_vertical - webcam_image.rows)/3), int((resolution_vertical - webcam_image.rows) / 2), int((resolution_horizontal - webcam_image.cols) / 2), int((resolution_horizontal - webcam_image.cols) / 2), 0, Scalar(50, 50, 50));
	imshow("REDOX", webcam_image);
	imshow("CO2", gas_image);
	imshow("Thermal", thermal_image);
	moveWindow("REDOX", 0, 0);
	moveWindow("Thermal", 0, 0);
	moveWindow("CO2", 0, thermal_height * upscale_factor);
}

void setup(int argc, char** argv) 
{
	ConnectSoX();
	ConnectROS(argc, argv);
	InitializeGamepad();
	namedWindow("REDOX", WINDOW_AUTOSIZE);
	namedWindow("Claw");
	namedWindow("Processing");
	namedWindow("CO2");
	namedWindow("Thermal");
	CreateServoSliders();
	CreateModeButtons();
	capture.open(current_camera_index);
	InitializeQR();
	InitializeHazmat();
}

void loop()
{
	checkUserInput();
	checkSensorsFeed();
	updateInterface();
	waitKey(1);
}

int main(int argc, char** argv)
{
	setup(argc, argv);
	while (true)
	{
		loop();
	}
	return 0;
}