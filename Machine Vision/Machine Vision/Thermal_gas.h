#pragma once
#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
#define MAX_GAS_VALUE 3000
#define MAX_TEMP_VALUE 50
#define MIN_TEMP_VALUE 0
const int thermal_width = 8;
const int thermal_height = 8;
const int upscale_factor = 20;
const int thermal_width_upscaled = thermal_width * upscale_factor;
const int thermal_height_upscaled = thermal_height * upscale_factor;
Mat thermal_image = Mat::zeros(Size(thermal_width, thermal_height), CV_32FC1);
Mat gas_image = Mat::zeros(Size(thermal_width_upscaled, thermal_height_upscaled * 0.4), CV_8UC3);

void UpdateGas(int current_gas)
{
	gas_image = Mat::zeros(Size(thermal_width_upscaled, thermal_height_upscaled * 0.4), CV_8UC3);
	float rectangle_width = (float(current_gas) / MAX_GAS_VALUE) * float(thermal_width_upscaled);
	rectangle(gas_image, Point(0, 0), Point(thermal_width_upscaled, thermal_height_upscaled * 0.4), Scalar(255, 255, 255), FILLED);
	rectangle(gas_image, Point(0, 0), Point(rectangle_width, thermal_height_upscaled * 0.4), Scalar(0, 255, 255), FILLED);
	putText(gas_image, to_string(current_gas) + " ppm", Point(0, gas_image.rows / 2), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 0));
}

void UpdateThermal(float current_temperature[thermal_width * thermal_height])
{
	thermal_image = Mat(thermal_height, thermal_width, CV_32FC1, current_temperature);
	resize(thermal_image, thermal_image, Size(), upscale_factor, upscale_factor, INTER_LINEAR);
}