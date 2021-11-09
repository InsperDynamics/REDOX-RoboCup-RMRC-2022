#pragma once
#include <opencv2\opencv.hpp>
#include <iostream>
#include <time.h>

static cv::Mat fgMaskKNN;
static cv::Ptr<cv::BackgroundSubtractor> pKNN = cv::createBackgroundSubtractorKNN(60);

static cv::Mat DetectMotion(cv::Mat image)
{
	pKNN->apply(image, fgMaskKNN);
	cv::Mat eroded;
	cv::erode(fgMaskKNN, eroded, 1);
	cv::Mat no_noise;
	cv::medianBlur(eroded, no_noise, 3);
	std::vector<std::vector<cv::Point>> contours1;
	std::vector<cv::Vec4i> hierarchy1;
	findContours(no_noise, contours1, hierarchy1, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	drawContours(image, contours1, -1, cv::Scalar(0, 255, 0), 2);
	return image;
}