#ifndef PACKET_HPP
#define PACKET_HPP

#include <cstdint>
#include <vector>
#include <cstring>

const uint32_t START_CODE = 0x12345678;
const uint32_t END_CODE = 0x87654321;
const int HEADER_SIZE = 28;
const int REQ_PACKET_TYPE = 0;

struct Packet {
    uint32_t start_code;
    uint32_t packet_type;
    uint32_t frame_ID;
    uint32_t packet_index;
    uint32_t total_packets;
    uint32_t data_size;
    uint32_t end_code;
    std::vector<uint8_t> data;

    std::vector<uint8_t> serialize() const;
};

#endif // PACKET_HPP
