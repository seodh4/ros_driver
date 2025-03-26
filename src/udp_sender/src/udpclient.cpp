#include "udpclient.hpp"
#include <iostream>
#include <boost/bind/bind.hpp>

UDPClient::UDPClient(boost::asio::io_context& io,
                     const std::string& ip, unsigned short port,
                     IParser* parser)
    : socket_(io),
      server_endpoint_(boost::asio::ip::make_address(ip), port),
      parser_(parser) {
    socket_.open(boost::asio::ip::udp::v4());
    start_send();
    start_receive();
}

void UDPClient::send_packet(Packet& packet) {
    std::vector<uint8_t> serialized = packet.serialize();
    socket_.async_send_to(boost::asio::buffer(serialized), server_endpoint_,
        std::bind(&UDPClient::handle_send, this, std::placeholders::_1, std::placeholders::_2));
}

void UDPClient::start_send() {
    std::string msg = "Ping from client";
    socket_.async_send_to(boost::asio::buffer(msg), server_endpoint_,
        std::bind(&UDPClient::handle_send, this, std::placeholders::_1, std::placeholders::_2));
}

void UDPClient::handle_send(const boost::system::error_code& ec, std::size_t len) {
    if (!ec)
        std::cout << "[Client] Sent (" << len << " bytes)" << std::endl;
}

void UDPClient::start_receive() {
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), sender_endpoint_,
        std::bind(&UDPClient::handle_receive, this, std::placeholders::_1, std::placeholders::_2));
}

void UDPClient::handle_receive(const boost::system::error_code& ec, std::size_t len) {
    if (!ec) {
        std::vector<uint8_t> data(recv_buffer_.begin(), recv_buffer_.begin() + len);
        parser_->push_data(std::move(data));
        start_receive();
    }
}
