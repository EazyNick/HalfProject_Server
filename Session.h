#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <array>
#include <memory>
#include <string>

using boost::asio::ip::tcp;

class SessionManager;  // ���� ����

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket);
        // Session�� tcp::socket socket �� �Ű������� �޴� �����ڸ� ����
    //Session�� �����ڸ� ���� ���, �Ʒ� �⺻ ������ �߰����ֱ�
    //Session() = default; // �⺻ �����ڸ� �����Ϸ��� ���� �ڵ� ����
    //virtual ~Session() = default; // ���� �Ҹ��ڸ� �����մϴ�. 
    // ���� �Ҹ��ڴ� �Ļ� Ŭ�������� ��ü�� �Ҹ�� �� �ʿ��� �ڿ� ������ �ùٸ��� �ϱ� ���� ���
        
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
    // Ŭ���̾�Ʈ ���� ������ ���� �����̳�
    //int client_id_;
    tcp::socket socket_;
    std::array<char, 1024> data_;
    //SessionManager& session_manager_;
    /*
    ��Ʈ��ũ ��ſ��� �����͸� ���� �� std::array �Ǵ� �Ϲ� �迭(char[])�� ����ϴ� ������ 
    ��Ʈ��ũ���� �޴� �����Ͱ� ���� ����Ʈ �����̱� �����Դϴ�. �� �����ʹ� �ܼ��� ���ڿ� �Ӹ� �ƴ϶�, 
    �̹���, ����, ���� ���� �� ��� ������ �����͵� �� �� ������, 
    �̸� ��� ó���ϱ� ���� �Ϲ������� ���� ����Ʈ �迭�� ���
    */
};

#endif // SESSION_H
