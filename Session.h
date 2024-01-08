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
    ��Ʈ��ũ ��ſ��� �����͸� ���� �� std::array �Ǵ� �Ϲ� �迭(char[])�� ����ϴ� ������ 
    ��Ʈ��ũ���� �޴� �����Ͱ� ���� ����Ʈ �����̱� �����Դϴ�. �� �����ʹ� �ܼ��� ���ڿ� �Ӹ� �ƴ϶�, 
    �̹���, ����, ���� ���� �� ��� ������ �����͵� �� �� ������, 
    �̸� ��� ó���ϱ� ���� �Ϲ������� ���� ����Ʈ �迭�� ���
    */
};

#endif // SESSION_H
