#pragma once
#include <opencv2\opencv.hpp>
#include <iostream>

static cv::Mat fgMaskKNN;
static cv::Ptr<cv::BackgroundSubtractor> pKNN = cv::createBackgroundSubtractorKNN(60, 100, false);

static cv::Mat DetectMotion(cv::Mat image)
{
	pKNN->apply(image, fgMaskKNN);
	cv::Mat eroded;
	cv::erode(fgMaskKNN, eroded, 1);
	cv::Mat no_noise;
	cv::medianBlur(eroded, no_noise, 3);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy1;
	findContours(no_noise, contours, hierarchy1, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++)
	{
		if (cv::contourArea(contours[i]) > 100)
			drawContours(image, contours, i, cv::Scalar(0, 255, 0), 2);
	}
	return image;
}