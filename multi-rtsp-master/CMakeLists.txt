cmake_minimum_required(VERSION 3.0.2)
project(multi_rtsp)

## 查找catkin的依赖项
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  image_transport
  cv_bridge
)

## 查找OpenCV
find_package(OpenCV REQUIRED)

## 包含头文件目录
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

## 声明catkin包
catkin_package()

## 添加可执行文件
add_executable(multi_rtsp_node src/muti-rtsp.cpp)

## 链接库
target_link_libraries(multi_rtsp_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)