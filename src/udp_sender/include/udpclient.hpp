#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

#include <boost/asio.hpp>
#include <functional>
#include <array>
#include <string>
#include <vector>
#include "iparser.hpp"
#include "packet.hpp"

class UDPClient {
public:
    UDPClient(boost::asio::io_context& io,
              const std::string& ip, unsigned short port,
              IParser* parser);

    void send_packet(Packet& packet);

private:
    void start_send();
    void handle_send(const boost::system::error_code& ec, std::size_t len);
    void start_receive();
    void handle_receive(const boost::system::error_code& ec, std::size_t len);

    IParser* parser_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint server_endpoint_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    std::array<uint8_t, 1500> recv_buffer_;
};

#endif // UDPCLIENT_HPP
