#include "client_session.h"
#include "Logger.h"

// 정적 멤버 변수 초기화
unsigned long long client_session::next_id = 1;

// client_session 클래스의 생성자를 정의합니다. 이 생성자는 tcp::socket 타입의 객체를 매개변수로 받음
// 부모 클래스 Session의 생성자를 초기화합니다. 
// std::move(socket)는 socket 매개변수를 이동 시멘틱으로 전달하여 리소스 복사를 방지
client_session::client_session(tcp::socket socket)
    : Session(std::move(socket)), client_id(next_id++) {}

    
void client_session::initialize() {
    next_id = 1;
}

unsigned long client_session::get_client_id() const {
    Logger::GetInstance().log("ID:" + std::to_string(client_id));
    return client_id;
}

void client_session::start() {

    client_session::get_client_id();
    Session::start();

    // 데이터 수신 및 전송 로직 구현
}
