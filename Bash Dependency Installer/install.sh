#!/bin/bash

# Before using the script make sure cmake and pip3 are up-to-date
# Before using the script make sure internet connection is ok

cd ~

sudo apt update
sudo apt upgrade

sudo apt install curl
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt update
sudo apt install ros-melodic-desktop-full
apt search ros-melodic
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
sudo rosdep init
rosdep update
cd ~

git clone https://github.com/libsdl-org/SDL
mkdir build
cd build
../configure
make
sudo make install
cd ~

git clone https://github.com/JetsonHacksNano/installLibrealsense
cd installLibrealsense
./installLibrealsense.sh
cd ~

sudo apt install cmake pkg-config
sudo apt-get install python swig
git clone https://github.com/YDLIDAR/YDLidar-SDK.git
cd YDLidar-SDK
mkdir build
cd build
cmake ..
make
sudo make install
cd ..
pip3 install .
cd ~

sudo apt-get install libzbar-dev

sudo apt-get install libcanberra-gtk-module

sudo apt install sox

sudo snap install arduino

sudo apt update
sudo apt install software-properties-common apt-transport-https wget
wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"
sudo apt install code

sudo reboot

# After running this script, you can setup ros workspace, upload the Arduino code, recompile the machine vision interface, and setup VNC.