#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "Realsense_images.h"
#include "ROS_communication.h"
#include "Gamepad_controller.h"
#include "Claw.h"
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
int current_camera = 1;
VideoCapture capture;
VideoCapture captureClaw;
Mat webcam_image;

void openCamera(int index)
{
	//1 = t265(front), 2 = c920(back), 3 = ov5647(claw)
	if (index == 1 || index == 2)
	{
		if (captureClaw.isOpened())
			captureClaw.release();
		if (!capture.isOpened())
			capture.open(0);
		capture.set(CAP_PROP_FPS, 30);
		capture.set(CAP_PROP_CONVERT_RGB, false);
	}
	else if (index == 3)
	{
		if (capture.isOpened())
			capture.release();
		captureClaw = VideoCapture(csi_gstreamer_pipeline(resolution_horizontal, resolution_vertical), CAP_GSTREAMER);
	}
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
		if (gamepad_command == "previous_camera")
			current_camera--;
		else if (gamepad_command == "next_camera")
			current_camera++;
		if (current_camera < 0)
			current_camera = 3;
		else if (current_camera > 3)
			current_camera = 0;
		openCamera(current_camera);
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
	else if (autonomous_movement)
	{
		int pwm_l = 0;
		int pwm_r = 0;
		//transform cmdvel_linear_x and cmdvel_angular_z to pwm_l and pwm_r
		if (current_camera == 2)
		{
			int temp = pwm_l;	
			pwm_l = -pwm_r;
			pwm_r = -temp;
		}
		cout << gamepad_command << " " << to_string(pwm_l) << " " << to_string(pwm_r) << "\n";
		WriteArduino(gamepad_command, pwm_l, pwm_r);
	}
}

void checkSensorsFeed()
{
	ReadArduino();
	UpdateGas(current_gas);
	UpdateThermal(current_temperature);
	if (current_camera == 1)
		webcam_image = ReadRealsenseWebcam();
	else if (current_camera == 2)
		capture >> webcam_image;
	else if (current_camera == 3)
		captureClaw.read(webcam_image);
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
	openCamera(1);
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