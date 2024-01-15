#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include <boost/asio.hpp>
#include "Session.h"

using boost::asio::ip::tcp;

// Session ���
class client_session : public Session {

public:
    //explicit�� �����ڰ� �� ���� �Ű������� ���� �� ���
    //�����ڷμ�, client_session �ʱ�ȭ
    explicit client_session(tcp::socket socket);
        
    unsigned long get_client_id() const; // Ŭ���̾�Ʈ ID�� ��ȯ�ϴ� �Լ�
    void start() override; // Session�� start�Լ��� ����ϱ� ����, virtual�� ����ؼ� �Ƚᵵ ������ ���������� ����.
    static void initialize();

private:
    int client_id_;
    static unsigned long long next_id;  // Ŭ���̾�Ʈ ID�� ���� ���� ��� ����, ī����
    unsigned long long client_id;       // �� Ŭ���̾�Ʈ ������ ���� ID ��� ����
};

#endif // CLIENT_SESSION_H
