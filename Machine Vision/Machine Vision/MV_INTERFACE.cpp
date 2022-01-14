#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
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
Mat thermal_image;
string incoming_msg;
string outgoing_msg;

static vector<string> splitstring(string str) {
	static vector<string> splitted;
	static string word = "";
	static int word_index = 0;
	for (auto c : str) {
		if (c == ',') {
			splitted.push_back(word);
			word_index++;
			word = "";
		}
		else {
			word += c;
		}
	}
	return splitted;
}


int main()
{
	GetDesktopResolution(resolution_horizontal, resolution_vertical);
	namedWindow("REDOX", WINDOW_AUTOSIZE);
	VideoCapture capture;
	capture.open(0);
	InitializeQR();
	//InitializeHazmat();
	while (true)
	{
		capture >> webcam_image;
		if (image_processing){
			//webcam_image = DetectHazmat(webcam_image);
			webcam_image = ReadQR(webcam_image);
			webcam_image = DetectMotion(webcam_image);
		}
		resizeWindow("REDOX", resolution_horizontal, resolution_vertical);
		copyMakeBorder(webcam_image, webcam_image, int((resolution_vertical - webcam_image.rows)/3), int((resolution_vertical - webcam_image.rows) / 2), int((resolution_horizontal - webcam_image.cols) / 2), int((resolution_horizontal - webcam_image.cols) / 2), 0, Scalar(55, 25, 16));
		imshow("REDOX", webcam_image);
		waitKey(1);
	}
	return 0;
}