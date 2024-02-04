#include "Session.h"
#include "SessionManager.h"
#include <iostream>
#include "MySQLData/DataRead.h"
#include "Logger.h"

template <typename T>   
bool checkType(const T& value) {
    if constexpr (std::is_same<T, std::string>::value) {
        std::cout << "Type is std::string" << std::endl;
        return true;
    }
    else {
        std::cout << "Type is not std::string" << std::endl;
        return false;
    }
}

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}

void Session::start(std::string client_id) {
    Logger::GetInstance().log(client_id + " " + "Client connected.");
    read();
}

void Session::start() {
    Logger::GetInstance().log("Client connected.");
    read();
}

void Session::read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_),

        [this, self](const boost::system::error_code& ec, std::size_t length) {
            if (!ec) {
                Logger::GetInstance().log("read");
                //data_.data()�� �迭�� ù ��° ��Ҹ� ����Ű�� �����͸� ��ȯ, H, e, l, l, o���� H�� ����Ŵ
                //length�� data_ �迭�� ����� ��ȿ�� ���ڿ� �������� ����Ʈ ���� �ǹ�, 5 Byte
                //data_�� ['H','l','l','l','o']�� ������ �� 
                //'' �� ����, ""�� ���ڿ�
                std::string received_data(data_.data(), length);
                Logger::GetInstance().log("Received: " + received_data);
                //std::cout << "Received data length: " << length << " bytes" << std::endl;

                const std::string database_ = "example_db";

                int test = 1234;

                if (test == 12345) {
                    Logger::GetInstance().log("received_data == hello");
                    std::vector<std::string> DBData = readDataFromDB(kDatabaseServer, kDatabaseUsername, kDatabasePassword, database_);
                    
                    //std::cout << "Received data length: " << length << " bytes" << std::endl;
                    
                    write(DBData);
                }
                else if (checkType(received_data)) {

                    //write(length);

                    SessionManager& manager = SessionManager::GetInstance();

                    // (int i = 1; i < 100; ++i) {
                        auto session1 = manager.get_session(1);
                        auto session2 = manager.get_session(2);
                        auto session4 = manager.get_session(4);
                        //if (session2) {
                        //    //2�� Ŭ���̾�Ʈ���� ������ ����
                        //    session2->write(length);
                        //}
                    //}
                        if (session1) {
                            if (session4) {
                                session4->write(received_data); // ������ �ڵ�
                                //session2->write(length);
                            }
                            else {
                                //read();
                            }
                            read();
                        }
                }
                else
                {
                    write(length);
                }
            }
            else {
                if (ec == boost::asio::error::eof) {
                    Logger::GetInstance().log("Client disconnected.");
                }
                else {
                    Logger::GetInstance().log("Read error: " + ec.message());
                    std::cerr << "Read error: " << ec.message() << std::endl;
                }
                std::fill(data_.begin(), data_.end(), 0); // ���۸� 0���� �ʱ�ȭ
            }
        });
}

// Write ���� ����, �Ű����� �� �ٸ�.
void Session::write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_.data(), length), // null���� �������� ��� ����
        [this, self](const boost::system::error_code& ec, std::size_t) {
            if (!ec) {
                Logger::GetInstance().log("Write Message");
                read();
            }
            else {
                std::cerr << "Write error: " << ec.message() << std::endl;
                Logger::GetInstance().log(ec.message());
            }
        });
}

void Session::write(const std::vector<std::string>&data) {
    auto self(shared_from_this());
    // �� ���ڿ��� ��ȸ�ϸ鼭 async_write ȣ��
    for (const auto& str : data) {
        boost::asio::async_write(socket_, boost::asio::buffer(str),
            [this, self](const boost::system::error_code& ec, std::size_t) {
                if (!ec) {
                    Logger::GetInstance().log("Write Message");
                    read();
                }
                else {
                    std::cerr << "Write error: " << ec.message() << std::endl;
                    Logger::GetInstance().log(ec.message());
                }
            });
    }

}

void Session::write(const std::string& data) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data), // std::string�� ������ ����
        [this, self](const boost::system::error_code& ec, std::size_t /*bytes_transferred*/) {
            if (!ec) {
                Logger::GetInstance().log("Write Message");
                // ���� �б� �۾��� ������ �� �ֽ��ϴ�.
                read();
            }
            else {
                Logger::GetInstance().log("Write error: " + ec.message());
            }
        });
}