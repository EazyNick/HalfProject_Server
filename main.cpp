#include "server.h"
#include <iostream>

int main() {
    try {
        unsigned short port_number = 12332;

        boost::asio::io_service io_service;

        Server server(io_service, port_number);
        server.run();

    }

    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // ���翡�� ���ǹ��� �ڵ�
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}


