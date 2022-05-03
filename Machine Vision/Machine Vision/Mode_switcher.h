#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int autonomous_movement = 0;
int qr_detection = 0;
int hazmat_detection = 0;
int motion_detection = 0;

void CreateModeButtons()
{
	createTrackbar("Autonomous explore", "Processing", &autonomous_movement, 1);
    createTrackbar("QR detect", "Processing", &qr_detection, 1);
    createTrackbar("Hazmat detect", "Processing", &hazmat_detection, 1);
    createTrackbar("Motion detect", "Processing", &motion_detection, 1);
}