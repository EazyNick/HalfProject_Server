#include "Session.h"
#include <iostream>
#include "DataRead.h"
#include "Logger.h"

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
                //data_�� ["H","l","l","l","o"]�� ������ ��
                std::string received_data(data_.data(), length);
                Logger::GetInstance().log("Received: " + received_data);
                //std::cout << "Received data length: " << length << " bytes" << std::endl;

                const std::string database_ = "example_db";

                if (received_data == "hello") {
                    Logger::GetInstance().log("received_data == hello");
                    std::vector<std::string> DBData = readDataFromDB(kDatabaseServer, kDatabaseUsername, kDatabasePassword, database_);
                    
                    //std::cout << "Received data length: " << length << " bytes" << std::endl;
                    
                    write(DBData);
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
    Logger::GetInstance().log("Write Message");
    boost::asio::async_write(socket_, boost::asio::buffer(data_.data(), length), // null���� �������� ��� ����
        [this, self](const boost::system::error_code& ec, std::size_t) {
            if (!ec) {
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
    Logger::GetInstance().log("Write Message");
    // �� ���ڿ��� ��ȸ�ϸ鼭 async_write ȣ��
    for (const auto& str : data) {
        boost::asio::async_write(socket_, boost::asio::buffer(str),
            [this, self](const boost::system::error_code& ec, std::size_t) {
                if (!ec) {
                    read();
                }
                else {
                    std::cerr << "Write error: " << ec.message() << std::endl;
                    Logger::GetInstance().log(ec.message());
                }
            });
    }
}
