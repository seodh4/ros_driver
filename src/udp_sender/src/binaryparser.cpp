#include "binaryparser.hpp"
#include <iostream>
#include <cstring>
#include "packet.hpp" // HEADER_SIZE 상수를 위해 포함

void BinaryParser::start() {
    is_running_ = true;
    worker_ = std::thread(&BinaryParser::consume, this);
}

void BinaryParser::stop() {
    is_running_ = false;
    queue_cv_.notify_all();
    if (worker_.joinable())
        worker_.join();
}

void BinaryParser::register_callback(CallbackType cb) {
    callback_ = cb;
}

void BinaryParser::push_data(std::vector<uint8_t>&& data) {
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        recv_queue_.push(std::move(data));
    }
    queue_cv_.notify_one();
}

void BinaryParser::consume() {
    while (is_running_) {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        queue_cv_.wait(lock, [this] { return !recv_queue_.empty() || !is_running_; });

        while (!recv_queue_.empty()) {
            
            auto data = std::move(recv_queue_.front());
            recv_queue_.pop();
            lock.unlock();

            process_packet(data);

            

            lock.lock();
        }
    }
}

void BinaryParser::process_packet(const std::vector<uint8_t>& data) {
    if (data.size() < HEADER_SIZE)
        return;

    uint32_t* header = reinterpret_cast<uint32_t*>(const_cast<uint8_t*>(data.data()));
    uint32_t packet_type = header[1];

    if (packet_type == 1) {
        uint32_t frame_ID = header[2];
        uint32_t packet_index = header[3];
        uint32_t total_packets = header[4];
        uint32_t data_size = header[5];
        total_packets_expected_ = total_packets;
        current_frame_ID_ = frame_ID;
        std::vector<uint8_t> packet_data(data.begin() + HEADER_SIZE, data.begin() + HEADER_SIZE + data_size);
        {
            std::lock_guard<std::mutex> lock(frame_mutex_);
            received_packets_[packet_index] = packet_data;
        }
        {
            std::lock_guard<std::mutex> lock(frame_mutex_);
            if (received_packets_.size() == total_packets_expected_) {
                std::cout << "good" << std::endl;
                
                // assemble_frame();
                if (callback_)
                    callback_(data);
                    received_packets_.clear();
                
                
                
                // 모든 패킷 수신 완료 시 프레임 조합 (assemble_frame 함수 등 필요)
            }
        }
    }
}


void BinaryParser::assemble_frame() {
    std::vector<uint8_t> frame_data;
    for (uint32_t i = 0; i < total_packets_expected_; i++) {
        auto it = received_packets_.find(i);
        if (it != received_packets_.end()) {
            frame_data.insert(frame_data.end(), it->second.begin(), it->second.end());
        }
    }
    std::cout << "프레임 " << current_frame_ID_ << " 조합 완료, 사이즈: " << frame_data.size() << " bytes.\n";
    if (callback_)
    callback_(frame_data);

    received_packets_.clear();
    // send_frame_request();
    // 실제 ROS2 퍼블리시는 이곳에서 수행 가능
}
