#pragma once
#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int thermal_width = 8;
int thermal_height = 8;
int upscale_factor = 20;
int CO2level = 0;
Mat thermal_image = Mat::zeros(Size(thermal_width, thermal_height), CV_8UC3);
Mat gas_image = Mat::zeros(Size(thermal_width, thermal_height * 0.4), CV_8UC3);

void UpdateGas(vector<string> splitted)
{
	CO2level = atoi(splitted.back().c_str());
	gas_image = Mat::zeros(Size(thermal_width, thermal_height * 0.4), CV_8UC3);
	float rectangle_width = (float(CO2level) / 8000) * float(thermal_width);
	rectangle(gas_image, Point(0, 0), Point(thermal_width, thermal_height * 0.4), Scalar(255, 255, 255), FILLED);
	rectangle(gas_image, Point(0, 0), Point(rectangle_width, thermal_height * 0.4), Scalar(0, 255, 255), FILLED);
	putText(gas_image, to_string(CO2level) + "ppm", Point(0, gas_image.rows / 2), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 0));
}

void UpdateThermal(vector<string> splitted)
{
	thermal_image = Mat::zeros(Size(thermal_width, thermal_height), CV_64FC1);
	for (int row = 0; row < thermal_height; row++)
	{
		for (int col = 0; col < thermal_width; col++)
		{
			int current_index = col + (row * thermal_width);
			if (current_index >= splitted.size())
			{
				return;
			}
			int mapped_temperature_at_point = atoi(splitted[current_index].c_str());
			thermal_image.at<Scalar>(Point(col, row)) = Scalar(255 - mapped_temperature_at_point, 0, mapped_temperature_at_point);
		}
	}
	resize(thermal_image, thermal_image, Size(), upscale_factor, upscale_factor, INTER_CUBIC);
}