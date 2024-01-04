#include <iostream>
#include "Server.h"

int main() {
    try {
        // 읽기, 쓰기 등 다른 boost 라이브러리를 동작하면, io_context에 다 저장됨.
        boost::asio::io_context io_context;
        Server server(io_context, 12332);
        //Boost.Asio의 이벤트 처리 루프를 시작, 네트워크 이벤트(예: 새로운 연결, 데이터 수신)를 처리하고, 관련 콜백 함수를 실행
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}






/*
// asynchronous(비동기적) Server
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>

using boost::asio::ip::tcp;

// std::enable_shared_from_this를 상속받아서 객체가 std::shared_ptr로 자기 자신을 관리할 수 있게 합니다
// std::shared_ptr를 사용하면 객체가 더 이상 필요하지 않을 때 자동으로 메모리가 해제, 스마트 포인터임.
// 클래스가 std::enable_shared_from_this를 상속받으면, 
// 해당 클래스의 인스턴스는 std::shared_ptr를 통해 안전하게 자기 자신을 참조
// public std::enable_shared_from_this<Session>를 상속 받음.
// std::enable_shared_from_this<Session>는 
// Session 인스턴스를 가리키는 std::shared_ptr<Session> 타입의 객체를 반환
//즉, 스마트 포인터를 사용하기 위해 해당 클래스를 상속받는다.
class Session : public std::enable_shared_from_this<Session> {
public:
    //Session 클래스의 생성자입니다. tcp::socket 객체를 인자(매개변수)로 받아 std::move를 사용하여
    //멤버 변수 socket_으로 초기화, 매개변수로 받은 socket을 socket_으로 이동시킴.
    Session(tcp::socket socket) : socket_(std::move(socket)) {}

    // 연결 시작 시 호출
    void start() {
        std::cout << "Client connected." << std::endl;
        read();
    }

    // 클라이언트로부터 데이터를 비동기적으로 읽음
    void read() {
        //shared_from_this()는 클래스 인스턴스를 가리키는 std::shared_ptr를 반환
        // self 변수를 현재 객체의 shared_ptr 인스턴스로 초기화
        // 비동기 작업 중에 Session 객체가 살아있도록 보장
        auto self(shared_from_this());
        // 비동기적으로 데이터 읽음
        socket_.async_read_some(boost::asio::buffer(data_),
            // [this, self] 캡처를 통해 self라는 shared_ptr 인스턴스를 생성
            // 데이터 읽기가 완료되었을 때 호출될 람다 함수, 람다 함수 형식임. [가져올 변수](매개변수){함수내용}
            // 오류 코드와 읽은 바이트의 길이를 인자로 받음
            [this, self](const boost::system::error_code& ec, std::size_t length) {
                if (!ec) {
                    // 받은 데이터 출력
                    std::cout << "Received: " << std::string(data_.data(), length) << "\n";
                    // write 메서드를 호출하여 데이터를 클라이언트에게 되돌려 보냅니다.
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
    // length 파라미터는 전송할 데이터의 길이
    // 데이터 전송 함수
    void write(std::size_t length) {
        // self라는 std::shared_ptr 변수를 현재 객체의 shared_ptr로 초기화
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(data_.data(), length),
            [this, self](const boost::system::error_code& ec, std::size_t) {
                if (!ec) {
                    // 에러가 없으면, 보내고 나서 추가적으로 데이터 받을 준비
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

// io_context와 port를 받아, tcp::acceptor 객체 acceptor_를 초기화하고 start_accept 메서드를 호출 
// 이 클래스는 네트워크 연결을 수락하고 Session 객체를 관리, io_context는 I/O 작업을 관리하기 위한 핵심 클래스
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
                    //새로운 Session 객체를 생성하고, start 메서드를 호출하여 클라이언트와의 통신을 시작
                    auto session = std::make_shared<Session>(std::move(socket));
                    session->start();  // session 함수 start 사용, 연결 성공 메시지를 출력하도록 함
                }
                else {
                    std::cerr << "Accept error: " << ec.message() << std::endl;
                }
                start_accept();  // 새로운 연결을 위해 계속 기다립니다.
            });
    }

    // 클라이언트의 연결 요청을 기다리고, 연결이 수립되면 Session 객체를 생성하여 통신을 처리하는 객체
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
