cmake_minimum_required(VERSION 3.16.3)

project(Redox)

find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  message_filters
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
  genmsg
)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${zbar_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Redox REDOX_INTERFACE.cpp)

target_link_libraries(Redox PUBLIC ${OpenCV_LIBS})
target_link_libraries(Redox PUBLIC ${ZBAR_LIBRARIES} zbar)
target_link_libraries(Redox PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(Redox PUBLIC ${catkin_LIBRARIES})
