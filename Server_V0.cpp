#include "server.h"
#include <iostream>
#include <thread>
#include <chrono>

Server::Server(boost::asio::io_service& io_service, unsigned short port_number)
        //������, 'acceptor_'�� IPv4 �ּҸ� ����ϰ�, �����ڷκ��� ���޹��� ��Ʈ ��ȣ(port_number)���� ������ ��ٸ����� ����
    : io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), port_number)) {}

    // ���� ���� �Լ�
    void Server::run() {
        // �޼��带 ȣ���Ͽ� ������ Ŭ���̾�Ʈ�� ���� ���
        accept_connections();
        // �ٷ� �Ʒ��� ����
    }

    // ���� ������ ����Ͽ� ����ؼ� Ŭ���̾�Ʈ�� ������ ����
    void Server::accept_connections() {
        while (true) {
            //���ο� ���ῡ ���� socket ��ü�� ����
            tcp::socket socket(io_service_);
            //Ŭ���̾�Ʈ�� ������ ���������� �����ϰ�, ����� ������ socket ������ ����
            acceptor_.accept(socket);

            //���� �ڵ� ��ü error�� ����
            boost::system::error_code error;
            //Ŭ���̾�Ʈ�κ��� �����͸� �н��ϴ�.���� �����ʹ� data_ �迭�� ����ǰ�, ���� ����Ʈ ���� length�� ����˴ϴ�.
            size_t length = socket.read_some(boost::asio::buffer(data_), error);

            if (error) {
                // ���� �߻� �� ������ ������ ����
                throw boost::system::system_error(error);
            }

            // ���� �����͸� std::string���� ��ȯ
            std::string received_message(data_.data(), length);

            // �ֿܼ� ���� �����͸� ���
            std::cout.write(data_.data(), length);
            std::cout << std::endl;

            
             // Ŭ���̾�Ʈ�κ��� ���� �޽����� "Hello, server �ѱ۵ǳ�?!\n"�� ��ġ�ϴ��� Ȯ��
            if (received_message == "Hello, server �ѱ۵ǳ�?!\n") {
                // ����ϴ� �޽����� ��ġ�ϸ� Ŭ���̾�Ʈ���� Ư�� ������ ����
                boost::asio::write(socket, boost::asio::buffer("Hello, client! �ѱ۵�!\n"));
            }
            else {
                // �׷��� �ʴٸ� �ٸ� �޽����� ���� ���� �ֽ��ϴ�.
                boost::asio::write(socket, boost::asio::buffer("Received different message.\n"));
            }
            // �޽��� Ȯ���� ���� 1�� ���
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
