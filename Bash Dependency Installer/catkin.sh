#!/bin/bash

cd ~
mkdir --parents catkin_ws/src
cd catkin_ws
catkin init
sudo apt-get install ros-melodic-catkin
echo "source ~/opt/ros/melodic/setup.bash" >> ~/.bashrc
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
source ~/.bashrc

cd ~
sudo apt-get install ros-melodic-realsense2-camera
cd ~/catkin_ws/src
git clone https://github.com/YDLIDAR/ydlidar_ros_driver.git ydlidar_ws/src/ydlidar_ros_driver
cd ..
catkin_make