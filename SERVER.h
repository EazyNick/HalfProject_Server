// SERVER.H 를 한번만 호출하기 위한 조건문
#ifndef SERVER_H 
#define SERVER_H

#include <boost/asio.hpp>
#include <array>

using boost::asio::ip::tcp;

class Server {
public:
    // 서버 객체 초기화
    Server(boost::asio::io_service& io_service, unsigned short port_number);
    // 서버 시작 함수
    void run();

private:
    // 클라이언트 연결 수락 함수
    void accept_connections();

    //네트워크 I/O 작업을 처리하기 위한 객체의 참조를 저장
    boost::asio::io_service& io_service_;
    //클라이언트의 연결을 수락하는 데 사용
    tcp::acceptor acceptor_;
    //데이터를 저장하기 위한 128 바이트 크기의 고정 크기 배열
    std::array<char, 128> data_;
};

//파일의 내용이 여기서 끝나고, 다음 번에 이 파일이 포함되려 할 때 포함되지 않게함.
#endif // SERVER_H