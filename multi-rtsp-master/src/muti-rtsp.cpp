#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

class RtspCamera {
public:
    std::string rtsp_address;
    std::string ros_image_topic;
    image_transport::Publisher image_publisher;
    std::thread capture_thread;
    std::mutex running_mutex;
    bool running;

    RtspCamera(const std::string& address, const std::string& topic, ros::NodeHandle& nh)
        : rtsp_address(address), ros_image_topic(topic), running(true) {
        // 初始化发布者
        image_transport::ImageTransport it(nh);
        image_publisher = it.advertise(ros_image_topic, 10);

        // 启动捕获线程
        capture_thread = std::thread(&RtspCamera::captureAndPublish, this);
    }

    ~RtspCamera() {
        {
            std::lock_guard<std::mutex> lock(running_mutex);
            running = false;
        }
        if (capture_thread.joinable()) {
            capture_thread.join();
        }
    }

    //捕获和发布图像
    void captureAndPublish() {
        cv::VideoCapture cap(rtsp_address);
        if (!cap.isOpened()) {
            std::cerr << "Error opening video stream: " << rtsp_address << std::endl;
            return;
        }

        std::cout << "Successfully opened video stream: " << rtsp_address << std::endl;

        cv::Mat frame;
        sensor_msgs::ImagePtr msg;

        while (ros::ok()) {
            {
                std::lock_guard<std::mutex> lock(running_mutex);
                if (!running) {
                    break;
                }
            }

            cap >> frame;
            if (frame.empty()) {
                std::cerr << "Received empty frame" << std::endl;
                break;
            }

            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
            image_publisher.publish(msg);

            ros::spinOnce();
        }
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "rtsp_camera_node");
    ros::NodeHandle nh;

    // 初始化RtspCamera对象,可以初始化复数个对象
    RtspCamera right("rtsp://192.168.100.64:8000/Streaming/Channels/101", "/camera/right", nh);
    RtspCamera mid("rtsp://admin:123456@192.168.100.65:8000/Streaming/Channels/101", "/camera/mid", nh);
    RtspCamera left("rtsp://user:pwd@192.168.100.66:8000/Streaming/Channels/101", "/camera/left", nh);

    // 保持节点运行
    ros::spin();

    return 0;
}
