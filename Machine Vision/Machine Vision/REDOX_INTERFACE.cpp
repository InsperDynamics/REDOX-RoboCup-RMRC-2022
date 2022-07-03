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
//Recommended resolution for monitor display: set to 1280x720
int resolution_horizontal = 800;
int resolution_vertical = 450;
const int number_of_cameras = 3;
int current_camera = 1;
VideoCapture capture;
Mat webcam_image;

void openCamera(int index)
{
	capture.open(index);
	capture.set(CAP_PROP_FPS, 30);
	capture.set(CAP_PROP_CONVERT_RGB, false);
}

void checkUserInput()
{
	UpdateServosInput();
	if (use_keyboard == false)
		UpdateGamepadInput();
	else
		UpdateKeyboardInput();
	if (gamepad_command == "previous_camera" || gamepad_command == "next_camera")
	{
		if (current_camera == 3)
			openCamera(0);
		if (gamepad_command == "previous_camera")
			current_camera--;
		else if (gamepad_command == "next_camera")
			current_camera++;
		if (current_camera < 0)
			current_camera = number_of_cameras;
		else if (current_camera > number_of_cameras)
			current_camera = 0;
		if (current_camera == 3)
			openCamera(1);
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
			if (current_camera == 2)
			{
				int temp = gamepad_value_1;	
				gamepad_value_1 = -gamepad_value_2;
				gamepad_value_2 = -temp;
			}
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
	resize(webcam_image, webcam_image, Size(resolution_horizontal, resolution_vertical), INTER_NEAREST);
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
	openCamera(0);
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