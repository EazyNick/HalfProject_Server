#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include "Session.h"
#include "SessionManager.h"

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, short port);

private:
    SessionManager session_manager_;
    void start_accept();
    tcp::acceptor acceptor_;
};

#endif // SERVER_H
