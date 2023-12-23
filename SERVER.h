// SERVER.H �� �ѹ��� ȣ���ϱ� ���� ���ǹ�
#ifndef SERVER_H 
#define SERVER_H

#include <boost/asio.hpp>
#include <array>

using boost::asio::ip::tcp;

class Server {
public:
    // ���� ��ü �ʱ�ȭ
    Server(boost::asio::io_service& io_service, unsigned short port_number);
    // ���� ���� �Լ�
    void run();

private:
    // Ŭ���̾�Ʈ ���� ���� �Լ�
    void accept_connections();

    //��Ʈ��ũ I/O �۾��� ó���ϱ� ���� ��ü�� ������ ����
    boost::asio::io_service& io_service_;
    //Ŭ���̾�Ʈ�� ������ �����ϴ� �� ���
    tcp::acceptor acceptor_;
    //�����͸� �����ϱ� ���� 128 ����Ʈ ũ���� ���� ũ�� �迭
    std::array<char, 128> data_;
};

//������ ������ ���⼭ ������, ���� ���� �� ������ ���ԵǷ� �� �� ���Ե��� �ʰ���.
#endif // SERVER_H