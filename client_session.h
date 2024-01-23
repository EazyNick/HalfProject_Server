#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include <boost/asio.hpp>
#include "Session.h"

using boost::asio::ip::tcp;

static std::atomic<int> client_counter(0);

// Session 상속
class client_session : public Session {

public:
    //explicit는 생성자가 한 개의 매개변수를 받을 때 사용
    //생성자로서, client_session 초기화
    client_session(tcp::socket socket);
        
    unsigned int get_client_id() const; // 클라이언트 ID를 반환하는 함수
    void start() override; // Session의 start함수를 사용하기 위함, virtual을 사용해서 안써도 되지만 가시적으로 편함.

private:
    int client_id_;
};

#endif // CLIENT_SESSION_H
