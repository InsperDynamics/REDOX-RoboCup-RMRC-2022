#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "Hazmat_detection.h"
Mat webcam_image;

int main(int argc, char** argv)
{
    capture.open(1);
    capture.set(CAP_PROP_FPS, 30);
	capture.set(CAP_PROP_CONVERT_RGB, false);
    InitializeHazmat();
    namedWindow("hazmat");
    while (true)
    {
        capture >> webcam_image;
        webcam_image = DetectHazmat(webcam_image);
        imshow("hazmat", webcam_image);
        waitKey(1);
    }
}