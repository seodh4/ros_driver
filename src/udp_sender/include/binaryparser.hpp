#ifndef BINARYPARSER_HPP
#define BINARYPARSER_HPP

#include "iparser.hpp"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <map>
#include <cstdint>

class BinaryParser : public IParser {
public:
    BinaryParser() = default;
    ~BinaryParser() override { stop(); }

    void start() override;
    void stop() override;
    void register_callback(CallbackType cb) override;
    void push_data(std::vector<uint8_t>&& data) override;

private:
    void consume();
    void process_packet(const std::vector<uint8_t>& data);
    void assemble_frame();

    std::mutex frame_mutex_;
    uint32_t total_packets_expected_ = 0;
    uint32_t current_frame_ID_ = 0;
    uint32_t frame_ID;
    std::map<uint32_t, std::vector<uint8_t>> received_packets_;

    std::queue<std::vector<uint8_t>> recv_queue_;
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    bool is_running_ = false;
    std::thread worker_;
    CallbackType callback_;
};

#endif // BINARYPARSER_HPP
