#include "server.h"
#include <iostream>
#include <thread>
#include <chrono>

Server::Server(boost::asio::io_service& io_service, unsigned short port_number)
        //생성자, 'acceptor_'는 IPv4 주소를 사용하고, 생성자로부터 전달받은 포트 번호(port_number)에서 연결을 기다리도록 설정
    : io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), port_number)) {}

    // 서버 시작 함수
    void Server::run() {
        // 메서드를 호출하여 실제로 클라이언트의 연결 대기
        accept_connections();
        // 바로 아래에 정의
    }

    // 무한 루프를 사용하여 계속해서 클라이언트의 연결을 수락
    void Server::accept_connections() {
        while (true) {
            //새로운 연결에 사용될 socket 객체를 생성
            tcp::socket socket(io_service_);
            //클라이언트의 연결을 동기적으로 수락하고, 연결된 소켓을 socket 변수에 연결
            acceptor_.accept(socket);

            //에러 코드 객체 error를 선언
            boost::system::error_code error;
            //클라이언트로부터 데이터를 읽습니다.읽은 데이터는 data_ 배열에 저장되고, 읽은 바이트 수는 length에 저장됩니다.
            size_t length = socket.read_some(boost::asio::buffer(data_), error);

            if (error) {
                // 에러 발생 시 서버에 에러를 던짐
                throw boost::system::system_error(error);
            }

            // 읽은 데이터를 std::string으로 변환
            std::string received_message(data_.data(), length);

            // 콘솔에 읽은 데이터를 출력
            std::cout.write(data_.data(), length);
            std::cout << std::endl;

            
             // 클라이언트로부터 받은 메시지가 "Hello, server 한글되냐?!\n"와 일치하는지 확인
            if (received_message == "Hello, server 한글되냐?!\n") {
                // 기대하는 메시지와 일치하면 클라이언트에게 특정 응답을 보냄
                boost::asio::write(socket, boost::asio::buffer("Hello, client! 한글돼!\n"));
            }
            else {
                // 그렇지 않다면 다른 메시지를 보낼 수도 있습니다.
                boost::asio::write(socket, boost::asio::buffer("Received different message.\n"));
            }
            // 메시지 확인을 위한 1초 대기
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
