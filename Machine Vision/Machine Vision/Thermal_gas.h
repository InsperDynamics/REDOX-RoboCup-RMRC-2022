#pragma once
#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int thermal_width = 8;
int thermal_height = 8;
int upscale_factor = 20;
Mat thermal_image = Mat::zeros(Size(thermal_width, thermal_height), CV_64FC1);
int CO2level = 0;

void UpdateGas(vector<string> splitted)
{
	CO2level = atoi(splitted.back().c_str());
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