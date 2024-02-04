#include "client_session.h"
#include "SessionManager.h"
#include "Logger.h"
#include <string>

//std::map<int, std::shared_ptr<client_session>> clients;

// client_session Ŭ������ �����ڸ� �����մϴ�. �� �����ڴ� tcp::socket Ÿ���� ��ü�� �Ű������� ����
// �θ� Ŭ���� Session�� �����ڸ� �ʱ�ȭ�մϴ�. 
// std::move(socket)�� socket �Ű������� �̵� �ø�ƽ���� �����Ͽ� ���ҽ� ���縦 ����
client_session::client_session(tcp::socket socket)
    : Session(std::move(socket)) {} // Session �����ڿ� socket�� manager ���� ����


//unsigned int client_session::get_client_id() const {
//    static int client_id_ = 0;
//    Logger::GetInstance().log("ID:" + std::to_string(client_id_));
//    return ++client_id_;    
//}       

//// You can use the send function from a client_session object like this:
//void send_to_client(int client_id, std::vector<std::string>& message) {
//    auto it = clients.find(client_id);
//    if (it != clients.end()) {
//        it->second->write(message);  // Use the inherited send function
//    }
//    else {
//        Logger::GetInstance().log("Client ID not found: " + std::to_string(client_id));
//    } 
//}


void client_session::start() {
    //std::string client_id = std::to_string(client_session::get_client_id());
    Session::start();

    // ������ ���� �� ���� ���� ����
}
