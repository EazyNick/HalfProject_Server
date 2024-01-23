#include "client_session.h"
#include "Logger.h"
#include <string>

// client_session 클래스의 생성자를 정의합니다. 이 생성자는 tcp::socket 타입의 객체를 매개변수로 받음
// 부모 클래스 Session의 생성자를 초기화합니다. 
// std::move(socket)는 socket 매개변수를 이동 시멘틱으로 전달하여 리소스 복사를 방지
client_session::client_session(tcp::socket socket)
    : Session(std::move(socket)), client_id_(client_counter.fetch_add(1)) {}

unsigned int client_session::get_client_id() const {
    Logger::GetInstance().log("ID:" + std::to_string(client_id_));
    return client_id_;
}

void client_session::start() {

    std::string client_id = std::to_string(client_session::get_client_id());
    Session::start(client_id);

    // 데이터 수신 및 전송 로직 구현
}
