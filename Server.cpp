#include "Server.h"
#include <iostream>

Server::Server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    start_accept();
}

void Server::start_accept() {
    acceptor_.async_accept(
        [this](const boost::system::error_code& ec, tcp::socket socket) {
            if (!ec) {
                auto session = std::make_shared<Session>(std::move(socket));
                session->start();
            }
            else {
                std::cerr << "Accept error: " << ec.message() << std::endl;
            }
            start_accept();
        });
}
