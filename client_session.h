#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include <boost/asio.hpp>
#include "Session.h"
#include "SessionManager.h"
#include <map>
#include <memory>

using boost::asio::ip::tcp;

//static std::atomic<int> client_counter(0);

// Session ���
class client_session : public Session {

public:
    //explicit�� �����ڰ� �� ���� �Ű������� ���� �� ���
    //�����ڷμ�, client_session �ʱ�ȭ
    client_session(tcp::socket socket);
        
    //void send_to_client(int client_id, std::vector<std::string>& message);
    //unsigned int get_client_id() const; // Ŭ���̾�Ʈ ID�� ��ȯ�ϴ� �Լ�
    void start() override; // Session�� start�Լ��� ����ϱ� ����, virtual�� ����ؼ� �Ƚᵵ ������ ���������� ����.
        //std::map<int, std::shared_ptr<client_session>> clients;

private:
    //member�� mutable�� ���������ν� �� Ư�� ����� const ��ü�� �Ϻζ� ����� �� ����
    //mutable unsigned int client_id_;
};

#endif // CLIENT_SESSION_H
