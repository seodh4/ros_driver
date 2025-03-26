#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>

class Handler {
public:
    void on_parsed_data(const std::vector<uint8_t>& data) {
        // std::cout << "[Handler] Parsed data (" << data.size() << " bytes): ";
        // for (auto byte : data)
        //     std::cout << std::hex << static_cast<int>(byte) << " ";
        // std::cout << std::dec << std::endl;
        // std::cout << "[Handler] Parsed data (" << data.size() << " bytes): ";
    }
};

#endif // HANDLER_HPP



