#include <iostream>
#include <opencv2\opencv.hpp>
#include "QR_read.h"
#include "Motion_detection.h"

int main()
{
	cv::VideoCapture capture;
	capture.open(0);
	std::cout << "FPS: " << capture.get(cv::CAP_PROP_FPS) << std::endl;
	cv::Mat image;
	InitializeQR();
	while (true)
	{
		capture >> image;
		image = ReadQR(image);
		image = DetectMotion(image);
		cv::imshow("Result", image);
		cv::waitKey(1);
	}
	return 0;
}