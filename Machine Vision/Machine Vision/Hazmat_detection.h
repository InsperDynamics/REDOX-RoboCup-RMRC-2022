#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
using namespace dnn;

Net network;

static void InitializeHazmat()
{
    string model = "yolov3-tiny.weights";
    string config = "yolov3-tiny.cfg";
    network = readNet(model, config, "Darknet");
    network.setPreferableBackend(DNN_BACKEND_DEFAULT);
    network.setPreferableTarget(DNN_TARGET_OPENCL);
}

static Mat DetectHazmat(Mat image)
{
    static Mat blobFromImg;
    bool swapRB = true;
    blobFromImage(image, blobFromImg, 1, Size(416, 416), Scalar(), swapRB, false);
    float scale = 1.0 / 255.0;
    network.setInput(blobFromImg, "", scale, 0);
    Mat outMat;
    network.forward(outMat);
    for (int j = 0; j < outMat.rows; ++j)
    {
        Mat scores = outMat.row(j).colRange(5, outMat.cols);
        Point PositionOfMax;
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
            stringstream ss;
            ss << PositionOfMax.x;
            string clas = ss.str();
            int color = PositionOfMax.x * 10;
            putText(image, clas, Point(left, top), 1, 2, Scalar(color, 255, 255), 2, false);
            stringstream ss2;
            ss << confidence;
            string conf = ss.str();
            rectangle(image, Rect(left, top, width, height), Scalar(color, 0, 0), 2, 8, 0);
        }
    }
    return image;
}