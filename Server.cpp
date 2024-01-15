#include "Server.h"
#include <iostream>
#include "Logger.h"
#include "client_session.h"

Server::Server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {

    start_accept();
}

void Server::start_accept() {
    acceptor_.async_accept(
        [this](const boost::system::error_code& ec, tcp::socket socket) {
            if (!ec) {
                auto session = std::make_shared<client_session>(std::move(socket));
                session->start();
            }
            else {
                std::cerr << "Accept error: " << ec.message() << std::endl;
                Logger::GetInstance().log("Client connected.");
            }
            start_accept();
        });
}
