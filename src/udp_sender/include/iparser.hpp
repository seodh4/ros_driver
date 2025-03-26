#ifndef IPARSER_HPP
#define IPARSER_HPP

#include <vector>
#include <functional>

class IParser {
public:
    using CallbackType = std::function<void(const std::vector<uint8_t>&)>;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void register_callback(CallbackType cb) = 0;
    virtual void push_data(std::vector<uint8_t>&& data) = 0;
    
    virtual ~IParser() = default;
};

#endif // IPARSER_HPP
