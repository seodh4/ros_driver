#include "packet.hpp"
#include <cstring>

std::vector<uint8_t> Packet::serialize() const {
    std::vector<uint8_t> buffer(HEADER_SIZE + data_size);
    uint32_t* header = reinterpret_cast<uint32_t*>(buffer.data());
    header[0] = start_code;
    header[1] = packet_type;
    header[2] = frame_ID;
    header[3] = packet_index;
    header[4] = total_packets;
    header[5] = data_size;
    header[6] = end_code;
    if (data_size > 0 && data.size() >= data_size) {
        std::memcpy(buffer.data() + HEADER_SIZE, data.data(), data_size);
    }
    return buffer;
}
