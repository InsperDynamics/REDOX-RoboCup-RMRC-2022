#include <iostream>
#include <opencv2\opencv.hpp>
#include "QR_read.h"

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
		ReadQR(image);
	}
	return 0;
}