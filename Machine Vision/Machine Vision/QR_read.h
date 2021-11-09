#pragma once
#include <zbar.h>
#include <opencv2\opencv.hpp>
#include <numeric>
#include <fstream>

static zbar::ImageScanner scanner;
static cv::Mat image;
static cv::Mat imageGray;
static std::vector<cv::Point2f> obj_location;
static std::vector<std::string> qr_results{};
static std::ofstream myfile;

static cv::Point getCentroid(cv::InputArray Points)
{
	cv::Point Coord;
	cv::Moments mm = cv::moments(Points, false);
	double moment10 = mm.m10;
	double moment01 = mm.m01;
	double moment00 = mm.m00;
	Coord.x = int(moment10 / moment00);
	Coord.y = int(moment01 / moment00);
	return Coord;
}

static void InitializeQR() 
{
	scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
	myfile.open("qr_results.txt");
}


static cv::Mat ReadQR(cv::Mat image)
{
	cv::Mat imageGray;
	cv::cvtColor(image, imageGray, cv::COLOR_RGB2GRAY);
	int width = imageGray.cols;
	int height = imageGray.rows;
	uchar* raw = (uchar*)imageGray.data;
	zbar::Image imageZbar(width, height, "Y800", raw, width * height);
	scanner.scan(imageZbar);
	zbar::Image::SymbolIterator symbol = imageZbar.symbol_begin();
	if (imageZbar.symbol_begin() != imageZbar.symbol_end())
	{
		for (; symbol != imageZbar.symbol_end(); ++symbol)
		{
			for (int i = 0; i < symbol->get_location_size(); i++)
			{
				obj_location.push_back(cv::Point(symbol->get_location_x(i), symbol->get_location_y(i)));
			}
			for (int i = 0; i < obj_location.size(); i++)
			{
				cv::line(image, obj_location[i], obj_location[(i + 1) % obj_location.size()], cv::Scalar(255, 0, 0), 3);
			}
			cv::String text = symbol->get_data();
			int fontFace = cv::FONT_HERSHEY_SIMPLEX;
			double fontScale = 1.1;
			int thickness = 2;
			cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, 0);
			cv::Point textOrg(getCentroid(obj_location).x - (textSize.width / 2), getCentroid(obj_location).y);
			cv::putText(image, text, textOrg, fontFace, fontScale, (0, 0, 255), thickness);
			obj_location.clear();
			if (std::find(qr_results.begin(), qr_results.end(), symbol->get_data()) == qr_results.end())
			{
				myfile << "\nDecode Result: " << std::endl << symbol->get_data() << std::endl;
			}
			qr_results.push_back(symbol->get_data());
		}
		imageZbar.set_data(NULL, 0);
	}
	return image;
}