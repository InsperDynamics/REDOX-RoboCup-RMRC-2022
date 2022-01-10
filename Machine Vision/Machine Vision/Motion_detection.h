#pragma once
#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat firstFrame;

static Mat DetectMotion(Mat image)
{
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(21, 21), 0);
	if (firstFrame.empty())
	{
		firstFrame = gray;
	}
	Mat frameDelta;
	absdiff(firstFrame, gray, frameDelta);
	Mat DeltaThresholded;
	double thresh = threshold(frameDelta, DeltaThresholded, 25, 255, THRESH_BINARY);
	Mat dilate_kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(2, 2));
	dilate(DeltaThresholded, DeltaThresholded, dilate_kernel, Point(-1, -1), 2);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	DeltaThresholded.convertTo(DeltaThresholded, CV_8UC1);
	findContours(DeltaThresholded, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (size_t c = 0; c < contours.size(); c++)
	{
		drawContours(image, contours, (int)c, Scalar(0, 0, 255), 2);
	}
	firstFrame = gray;
	return image;
}