#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <array>
#include <memory>
#include <string>

using boost::asio::ip::tcp;

class SessionManager;  // 전방 선언

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket);
        // Session은 tcp::socket socket 를 매개변수로 받는 생성자를 가짐
    //Session이 생성자를 만들 경우, 아래 기본 생성자 추가해주기
    //Session() = default; // 기본 생성자를 컴파일러에 의해 자동 생성
    //virtual ~Session() = default; // 가상 소멸자를 정의합니다. 
    // 가상 소멸자는 파생 클래스에서 객체가 소멸될 때 필요한 자원 정리를 올바르게 하기 위해 사용
        
    virtual void start();
    virtual void start(std::string client_id);
    virtual void read();
    virtual void write(std::size_t length);
    virtual void write(const std::vector<std::string>& data);
    void write(const std::string& data);

    int get_client_id() const { 
        return client_id_;
    }
        
protected:
    unsigned int client_id_;

private:
    // 클라이언트 소켓 관리를 위한 컨테이너
    //int client_id_;
    tcp::socket socket_;
    std::array<char, 1024> data_;
    //SessionManager& session_manager_;
    /*
    네트워크 통신에서 데이터를 받을 때 std::array 또는 일반 배열(char[])을 사용하는 이유는 
    네트워크에서 받는 데이터가 원시 바이트 형태이기 때문입니다. 이 데이터는 단순한 문자열 뿐만 아니라, 
    이미지, 비디오, 이진 파일 등 어떠한 형태의 데이터도 될 수 있으며, 
    이를 모두 처리하기 위해 일반적으로 원시 바이트 배열을 사용
    */
};

#endif // SESSION_H
