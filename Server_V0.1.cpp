#include <iostream>
#include "Server.h"

int main() {
    try {
        // �б�, ���� �� �ٸ� boost ���̺귯���� �����ϸ�, io_context�� �� �����.
        boost::asio::io_context io_context;
        Server server(io_context, 12332);
        //Boost.Asio�� �̺�Ʈ ó�� ������ ����, ��Ʈ��ũ �̺�Ʈ(��: ���ο� ����, ������ ����)�� ó���ϰ�, ���� �ݹ� �Լ��� ����
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}






/*
// asynchronous(�񵿱���) Server
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>

using boost::asio::ip::tcp;

// std::enable_shared_from_this�� ��ӹ޾Ƽ� ��ü�� std::shared_ptr�� �ڱ� �ڽ��� ������ �� �ְ� �մϴ�
// std::shared_ptr�� ����ϸ� ��ü�� �� �̻� �ʿ����� ���� �� �ڵ����� �޸𸮰� ����, ����Ʈ ��������.
// Ŭ������ std::enable_shared_from_this�� ��ӹ�����, 
// �ش� Ŭ������ �ν��Ͻ��� std::shared_ptr�� ���� �����ϰ� �ڱ� �ڽ��� ����
// public std::enable_shared_from_this<Session>�� ��� ����.
// std::enable_shared_from_this<Session>�� 
// Session �ν��Ͻ��� ����Ű�� std::shared_ptr<Session> Ÿ���� ��ü�� ��ȯ
//��, ����Ʈ �����͸� ����ϱ� ���� �ش� Ŭ������ ��ӹ޴´�.
class Session : public std::enable_shared_from_this<Session> {
public:
    //Session Ŭ������ �������Դϴ�. tcp::socket ��ü�� ����(�Ű�����)�� �޾� std::move�� ����Ͽ�
    //��� ���� socket_���� �ʱ�ȭ, �Ű������� ���� socket�� socket_���� �̵���Ŵ.
    Session(tcp::socket socket) : socket_(std::move(socket)) {}

    // ���� ���� �� ȣ��
    void start() {
        std::cout << "Client connected." << std::endl;
        read();
    }

    // Ŭ���̾�Ʈ�κ��� �����͸� �񵿱������� ����
    void read() {
        //shared_from_this()�� Ŭ���� �ν��Ͻ��� ����Ű�� std::shared_ptr�� ��ȯ
        // self ������ ���� ��ü�� shared_ptr �ν��Ͻ��� �ʱ�ȭ
        // �񵿱� �۾� �߿� Session ��ü�� ����ֵ��� ����
        auto self(shared_from_this());
        // �񵿱������� ������ ����
        socket_.async_read_some(boost::asio::buffer(data_),
            // [this, self] ĸó�� ���� self��� shared_ptr �ν��Ͻ��� ����
            // ������ �бⰡ �Ϸ�Ǿ��� �� ȣ��� ���� �Լ�, ���� �Լ� ������. [������ ����](�Ű�����){�Լ�����}
            // ���� �ڵ�� ���� ����Ʈ�� ���̸� ���ڷ� ����
            [this, self](const boost::system::error_code& ec, std::size_t length) {
                if (!ec) {
                    // ���� ������ ���
                    std::cout << "Received: " << std::string(data_.data(), length) << "\n";
                    // write �޼��带 ȣ���Ͽ� �����͸� Ŭ���̾�Ʈ���� �ǵ��� �����ϴ�.
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
    // length �Ķ���ʹ� ������ �������� ����
    // ������ ���� �Լ�
    void write(std::size_t length) {
        // self��� std::shared_ptr ������ ���� ��ü�� shared_ptr�� �ʱ�ȭ
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(data_.data(), length),
            [this, self](const boost::system::error_code& ec, std::size_t) {
                if (!ec) {
                    // ������ ������, ������ ���� �߰������� ������ ���� �غ�
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

// io_context�� port�� �޾�, tcp::acceptor ��ü acceptor_�� �ʱ�ȭ�ϰ� start_accept �޼��带 ȣ�� 
// �� Ŭ������ ��Ʈ��ũ ������ �����ϰ� Session ��ü�� ����, io_context�� I/O �۾��� �����ϱ� ���� �ٽ� Ŭ����
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
                    //���ο� Session ��ü�� �����ϰ�, start �޼��带 ȣ���Ͽ� Ŭ���̾�Ʈ���� ����� ����
                    auto session = std::make_shared<Session>(std::move(socket));
                    session->start();  // session �Լ� start ���, ���� ���� �޽����� ����ϵ��� ��
                }
                else {
                    std::cerr << "Accept error: " << ec.message() << std::endl;
                }
                start_accept();  // ���ο� ������ ���� ��� ��ٸ��ϴ�.
            });
    }

    // Ŭ���̾�Ʈ�� ���� ��û�� ��ٸ���, ������ �����Ǹ� Session ��ü�� �����Ͽ� ����� ó���ϴ� ��ü
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
