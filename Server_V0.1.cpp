#include <iostream>
#include "Server.h"

int main() {
    try {
        boost::asio::io_context io_context;
        Server server(io_context, 12332);
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}









/*
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket) : socket_(std::move(socket)) {}

    // 연결 시작 시 호출됩니다.
    void start() {
        std::cout << "Client connected." << std::endl;
        read();
    }

    void read() {
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

    void write(std::size_t length) {
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

private:
    tcp::socket socket_;
    std::array<char, 1024> data_;
};

class Server {
public:
    Server(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        start_accept();
    }

private:
    void start_accept() {
        acceptor_.async_accept(
            [this](const boost::system::error_code& ec, tcp::socket socket) {
                if (!ec) {
                    auto session = std::make_shared<Session>(std::move(socket));
                    session->start();  // 연결 성공 메시지를 출력하도록 start() 호출
                }
                else {
                    std::cerr << "Accept error: " << ec.message() << std::endl;
                }
                start_accept();  // 새로운 연결을 위해 계속 기다립니다.
            });
    }

    tcp::acceptor acceptor_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        Server server(io_context, 12332);
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
*/
