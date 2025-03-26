#include "rgbd_ros_driver.hpp"
#include <chrono>
#include <iostream>

rgbd_ros_driver::rgbd_ros_driver(const std::string& ip, unsigned short port)
    : parser_(),
      client_(io_context_, ip, port, &parser_) {
    parser_.register_callback(
        [this](const std::vector<uint8_t>& data) {
            handler_.on_parsed_data(data);
        }
    );
}

rgbd_ros_driver::~rgbd_ros_driver() {
    stop();
}

void rgbd_ros_driver::start() {
    parser_.start();
    io_thread_ = std::thread([this]() { io_context_.run(); });
}

void rgbd_ros_driver::stop() {
    io_context_.stop();
    if (io_thread_.joinable())
        io_thread_.join();
    parser_.stop();
}


void rgbd_ros_driver::send_udp_packet() {
    Packet packet;
    packet.start_code = START_CODE;
    packet.packet_type = REQ_PACKET_TYPE;
    packet.frame_ID = 0;
    packet.packet_index = 0;
    packet.total_packets = 1;
    packet.data_size = 0;
    packet.end_code = END_CODE;
    client_.send_packet(packet);
}