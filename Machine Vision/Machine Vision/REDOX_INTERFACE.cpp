#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "Realsense_images.h"
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
int resolution_horizontal = 1366;
int resolution_vertical = 768;
const int number_of_cameras = 3;
int current_camera = 1;
VideoCapture capture;
Mat webcam_image;

void checkUserInput()
{
	UpdateGamepadInput();
	UpdateServosInput();
	if (gamepad_command == "previous_camera" || gamepad_command == "next_camera")
	{
		if (gamepad_command == "previous_camera")
			current_camera--;
		else if (gamepad_command == "next_camera")
			current_camera++;
		if (current_camera < 0)
			current_camera = number_of_cameras;
		else if (current_camera > number_of_cameras)
			current_camera = 0;
		switch (current_camera)
		{
			case 1:
				//front camera, use ReadRealsenseWebcam()
				break;
			case 2:
				capture.open(0);
				capture.set(CAP_PROP_FPS, 30);
				break;
			case 3:
				capture.open(1);
				capture.set(CAP_PROP_FPS, 30);
				break;
		}
	}
	else if (!autonomous_movement)
	{
		if (!servos_command.empty())
		{
			cout << servos_command << "\n";
			WriteArduino(servos_command, servos_value, 0);
		}
		else if (!gamepad_command.empty())
		{
			cout << gamepad_command << " " << to_string(gamepad_value_1) << " " << to_string(gamepad_value_2) << "\n";
			WriteArduino(gamepad_command, gamepad_value_1, gamepad_value_2);
		}
	}
}

void checkSensorsFeed()
{
	ReadArduino();
	UpdateGas(current_gas);
	UpdateThermal(current_temperature);
	if (current_camera == 1)
		webcam_image = ReadRealsenseWebcam();
	else
		capture >> webcam_image;
	resize(webcam_image, webcam_image, Size(resolution_horizontal, resolution_vertical), INTER_LINEAR);
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
	imshow("REDOX", webcam_image);
	imshow("CO2", gas_image);
	imshow("Thermal", thermal_image);
	moveWindow("REDOX", 0, 0);
	moveWindow("Thermal", 0, 0);
	moveWindow("CO2", 0, thermal_height * upscale_factor);
}

void setup(int argc, char** argv) 
{
	system("gnome-terminal -- play '|rec --buffer 512 -d'");
	system("gnome-terminal -- roscore");
	ConnectROS(argc, argv);
	InitializeRealsenseWebcam();
	InitializeGamepad();
	namedWindow("REDOX", WINDOW_AUTOSIZE);
	namedWindow("Claw");
	namedWindow("Processing");
	namedWindow("CO2");
	namedWindow("Thermal");
	CreateServoSliders();
	CreateModeButtons();
	InitializeQR();
	InitializeHazmat();
}

void loop()
{
	checkUserInput();
	checkSensorsFeed();
	updateInterface();
	waitKey(30);
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