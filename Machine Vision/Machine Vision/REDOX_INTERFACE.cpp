#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
#include "Serial_communication.h"
#include "Thermal_gas.h"
#include "Screen_resolution.h"
#include "QR_read.h"
#include "Motion_detection.h"
#include "Hazmat_detection.h"
using namespace std;
using namespace cv;
bool image_processing = false;
int resolution_horizontal = 0;
int resolution_vertical = 0;
Mat webcam_image;


int main()
{
	//ConnectSerial();
	GetDesktopResolution(resolution_horizontal, resolution_vertical);
	namedWindow("REDOX", WINDOW_AUTOSIZE);
	VideoCapture capture;
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
		resizeWindow("REDOX", resolution_horizontal, resolution_vertical);
		copyMakeBorder(webcam_image, webcam_image, int((resolution_vertical - webcam_image.rows)/3), int((resolution_vertical - webcam_image.rows) / 2), int((resolution_horizontal - webcam_image.cols) / 2), int((resolution_horizontal - webcam_image.cols) / 2), 0, Scalar(50, 50, 50));
		imshow("REDOX", webcam_image);
		imshow("Thermal", thermal_image);
		moveWindow("Thermal", 0, 0);
		waitKey(1);
	}
	return 0;
}