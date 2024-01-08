#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <array>
#include <memory>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket);
    void start();
    void read();
    void write(std::size_t length);
    void write(const std::vector<std::string>& data);

private:
    tcp::socket socket_;
    std::array<char, 1024> data_;
    /*
    네트워크 통신에서 데이터를 받을 때 std::array 또는 일반 배열(char[])을 사용하는 이유는 
    네트워크에서 받는 데이터가 원시 바이트 형태이기 때문입니다. 이 데이터는 단순한 문자열 뿐만 아니라, 
    이미지, 비디오, 이진 파일 등 어떠한 형태의 데이터도 될 수 있으며, 
    이를 모두 처리하기 위해 일반적으로 원시 바이트 배열을 사용
    */
};

#endif // SESSION_H
