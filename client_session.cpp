#include "client_session.h"
#include "Logger.h"

// ���� ��� ���� �ʱ�ȭ
unsigned long long client_session::next_id = 1;

// client_session Ŭ������ �����ڸ� �����մϴ�. �� �����ڴ� tcp::socket Ÿ���� ��ü�� �Ű������� ����
// �θ� Ŭ���� Session�� �����ڸ� �ʱ�ȭ�մϴ�. 
// std::move(socket)�� socket �Ű������� �̵� �ø�ƽ���� �����Ͽ� ���ҽ� ���縦 ����
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

    // ������ ���� �� ���� ���� ����
}
