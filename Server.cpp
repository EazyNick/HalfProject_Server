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
                SessionManager& manager = SessionManager::GetInstance();
                int client_id = manager.generate_client_id();
                Logger::GetInstance().log("SessionManager : generate_client_id");
                manager.add_session(client_id, session); // SessionManager에 세션 추가
                Logger::GetInstance().log("SessionManager : add_session");
                //std::map<int, std::shared_ptr<client_session>> clients;
                //int client_id = session->get_client_id();
                //clients[client_id] = session;
                Logger::GetInstance().log(std::to_string(client_id) + " " + "ClinetConnectd");
                session->start();
            }
            else {
                std::cerr << "Accept error: " << ec.message() << std::endl;
                Logger::GetInstance().log("Client connected.");
            }
            start_accept();
        });
}
