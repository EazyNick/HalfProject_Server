#include "Session.h"
#include <iostream>

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}

void Session::start() {
    std::cout << "Client connected." << std::endl;
    read();
}

void Session::read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_),
        [this, self](const boost::system::error_code& ec, std::size_t length) {
            if (!ec) {
                std::cout << "Received: " << std::string(data_.data(), length) << "\n";
                write(length);
            }
            else {
                if (ec == boost::asio::error::eof) {
                    std::cout << "Client disconnected." << std::endl;
                }
                else {
                    std::cerr << "Read error: " << ec.message() << std::endl;
                }
            }
        });
}

void Session::write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_.data(), length),
        [this, self](const boost::system::error_code& ec, std::size_t) {
            if (!ec) {
                read();
            }
            else {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        });
}
