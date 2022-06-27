#pragma once
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
using namespace rs2;
pipeline pipe_rs;
config cfg_rs;
const int fisheye_sensor_idx = 2;

static void InitializeRealsenseWebcam()
{
    cfg_rs.enable_stream(RS2_STREAM_FISHEYE, 1, RS2_FORMAT_Y8);
    cfg_rs.enable_stream(RS2_STREAM_FISHEYE, 2, RS2_FORMAT_Y8);
    pipe_rs.start(cfg_rs);
}

static Mat ReadRealsenseWebcam()
{
    frameset frames = pipe_rs.wait_for_frames();
    video_frame fisheye_frame = frames.get_fisheye_frame(fisheye_sensor_idx);
    const int w = fisheye_frame.as<video_frame>().get_width();
    const int h = fisheye_frame.as<video_frame>().get_height();
    Mat fisheye_mat = Mat(Size(w, h), CV_8UC1, (void*)fisheye_frame.get_data(), Mat::AUTO_STEP);
    return fisheye_mat;
}