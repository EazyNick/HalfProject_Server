#include "client_session.h"
#include "Logger.h"
#include <string>

// client_session Ŭ������ �����ڸ� �����մϴ�. �� �����ڴ� tcp::socket Ÿ���� ��ü�� �Ű������� ����
// �θ� Ŭ���� Session�� �����ڸ� �ʱ�ȭ�մϴ�. 
// std::move(socket)�� socket �Ű������� �̵� �ø�ƽ���� �����Ͽ� ���ҽ� ���縦 ����
client_session::client_session(tcp::socket socket)
    : Session(std::move(socket)), client_id_(client_counter.fetch_add(1)) {}

unsigned int client_session::get_client_id() const {
    Logger::GetInstance().log("ID:" + std::to_string(client_id_));
    return client_id_;
}

void client_session::start() {

    std::string client_id = std::to_string(client_session::get_client_id());
    Session::start(client_id);

    // ������ ���� �� ���� ���� ����
}
