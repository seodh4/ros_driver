#ifndef RGBD_ROS_DRIVER_HPP
#define RGBD_ROS_DRIVER_HPP

#include <string>
#include <thread>
#include "udpclient.hpp"
#include "binaryparser.hpp"
#include "handler.hpp"
#include <boost/asio.hpp>
#include "packet.hpp"  // 패킷 상수 포함

class rgbd_ros_driver {
public:
    rgbd_ros_driver(const std::string& ip, unsigned short port);
    ~rgbd_ros_driver();
    void start();
    void stop();
    void send_udp_packet();

private:
    boost::asio::io_context io_context_;
    BinaryParser parser_;
    UDPClient client_;
    Handler handler_;
    std::thread io_thread_;
};

#endif // RGBD_ROS_DRIVER_HPP
