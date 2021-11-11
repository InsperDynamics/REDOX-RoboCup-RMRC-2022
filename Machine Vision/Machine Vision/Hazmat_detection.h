#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

cv::dnn::Net network;

static void InitializeHazmat()
{
    std::string model = "yolov3-tiny.weights";
    std::string config = "yolov3-tiny.cfg";
    network = cv::dnn::readNet(model, config, "Darknet");
    network.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
    network.setPreferableTarget(cv::dnn::DNN_TARGET_OPENCL);
}

static cv::Mat DetectHazmat(cv::Mat image)
{
    static cv::Mat blobFromImg;
    bool swapRB = true;
    cv::dnn::blobFromImage(image, blobFromImg, 1, cv::Size(416, 416), cv::Scalar(), swapRB, false);
    float scale = 1.0 / 255.0;
    network.setInput(blobFromImg, "", scale, 0);
    cv::Mat outMat;
    network.forward(outMat);
    for (int j = 0; j < outMat.rows; ++j)
    {
        cv::Mat scores = outMat.row(j).colRange(5, outMat.cols);
        cv::Point PositionOfMax;
        double confidence;
        minMaxLoc(scores, 0, &confidence, 0, &PositionOfMax);
        if (confidence > 0.0001)
        {
            int centerX = (int)(outMat.at<float>(j, 0) * image.cols);
            int centerY = (int)(outMat.at<float>(j, 1) * image.rows);
            int width = (int)(outMat.at<float>(j, 2) * image.cols + 20);
            int height = (int)(outMat.at<float>(j, 3) * image.rows + 100);
            int left = centerX - width / 2;
            int top = centerY - height / 2;
            std::stringstream ss;
            ss << PositionOfMax.x;
            std::string clas = ss.str();
            int color = PositionOfMax.x * 10;
            cv::putText(image, clas, cv::Point(left, top), 1, 2, cv::Scalar(color, 255, 255), 2, false);
            std::stringstream ss2;
            ss << confidence;
            std::string conf = ss.str();
            cv::rectangle(image, cv::Rect(left, top, width, height), cv::Scalar(color, 0, 0), 2, 8, 0);
        }
    }
    return image;
}