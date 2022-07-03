#!/bin/bash

cd ~
mkdir --parents catkin_ws/src
cd catkin_ws
catkin init
sudo apt-get install ros-melodic-catkin
echo "source ~/opt/ros/melodic/setup.bash" >> ~/.bashrc
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
source ~/.bashrc