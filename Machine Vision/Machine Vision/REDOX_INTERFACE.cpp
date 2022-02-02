#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
#include "Serial_communication.h"
#include "Gamepad_controller.h"
#include "Thermal_gas.h"
#include "Screen_resolution.h"
#include "QR_read.h"
#include "Motion_detection.h"
#include "Hazmat_detection.h"
using namespace std;
using namespace cv;
int number_of_cameras = 0;
Mat webcam_image;


int main(int argv, char** args)
{
	//ConnectSerial();
	InitializeGamepad();
	GetDesktopResolution(resolution_horizontal, resolution_vertical);
	namedWindow("REDOX", WINDOW_AUTOSIZE);
	VideoCapture capture;
	while (true) {
		if (!capture.open(number_of_cameras++)) {
			break;
		}
	}
	capture.open(0);
	InitializeQR();
	//InitializeHazmat();
	while (true)
	{
		//ReadSerial();
		if (!incoming_msg.empty())
		{
			vector<string> splitted = splitstring(incoming_msg);
			UpdateGas(splitted);
			splitted.pop_back();
			UpdateThermal(splitted);
		}
		capture >> webcam_image;
		if (image_processing){
			//webcam_image = DetectHazmat(webcam_image);
			webcam_image = ReadQR(webcam_image);
			webcam_image = DetectMotion(webcam_image);
		}
		outgoing_msg = GamepadCommand();
		if (outgoing_msg == "previous_camera")
		{

		}
		else if (outgoing_msg == "next_camera")
		{

		}
		else if (!outgoing_msg.empty())
		{
			cout << outgoing_msg;
			//WriteSerial(outgoing_msg);
		}
		resizeWindow("REDOX", resolution_horizontal, resolution_vertical);
		copyMakeBorder(webcam_image, webcam_image, int((resolution_vertical - webcam_image.rows)/3), int((resolution_vertical - webcam_image.rows) / 2), int((resolution_horizontal - webcam_image.cols) / 2), int((resolution_horizontal - webcam_image.cols) / 2), 0, Scalar(50, 50, 50));
		imshow("REDOX", webcam_image);
		imshow("CO2", gas_image);
		imshow("Thermal", thermal_image);
		moveWindow("Thermal", 0, 0);
		moveWindow("CO2", 0, thermal_height);
		waitKey(1);
	}
	return 0;
}