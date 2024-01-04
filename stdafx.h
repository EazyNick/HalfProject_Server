#pragma once
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class socket_server_tcp {
public:
    static const size_t buffer_size = 8192;

public:
    socket_server_tcp(boost::asio::io_context& io_context);
    ~socket_server_tcp();

    boost::asio::ip::tcp::socket& native_object() {
        return _socket;
    }

    void start_accept();

private:
    void read_complete(
        __in const boost::system::error_code& error,
        __in size_t bytes_received
    );

    void write(
        __in const void* data,
        __in const size_t size
    );

    void write_complete(
        __in const boost::system::error_code&,
        __in size_t
    );

    void reset();
    void read();
    void accept_complete(const boost::system::error_code& error);

private:
    int _sequence_number;
    char _receive_buffer[buffer_size];
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::ip::tcp::socket _socket;
};
