#include <iostream>
#include <opencv2\opencv.hpp>
#include "QR_read.h"
#include "Motion_detection.h"
#include "Hazmat_detection.h"
using namespace std;
using namespace cv;

int main()
{
	VideoCapture capture;
	capture.open(0);
	Mat image;
	InitializeQR();
	//InitializeHazmat();
	while (true)
	{
		cout << "FPS: " << capture.get(CAP_PROP_FPS) << endl;
		capture >> image;
		//image = DetectHazmat(image);
		//image = ReadQR(image);
		image = DetectMotion(image);
		imshow("Result", image);
		waitKey(1);
	}
	return 0;
}