#include "DataWrite.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <memory>

// 전역 변수
const string server = "tcp://localhost:12333";
const string username = "root";
const string password = "Password12#";
const string database = "example_db";

void initializeDatabase(const std::string& server, const std::string& username, const std::string& password, const std::string& database) {
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema(database);
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }
}

void createTable(const std::string& server, const std::string& username, const std::string& password, const std::string& database) {
    try {
        unique_ptr<sql::Connection> con(get_driver_instance()->connect(server, username, password));
        con->setSchema(database);
        unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("DROP TABLE IF EXISTS inventory");
        stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
        cout << "Finished creating table" << endl;
    }
    catch (sql::SQLException& e) {
        cout << "Error in createTable: " << e.what() << endl;
    }
}

void insertData(const std::string& server, const std::string& username, const std::string& password, const std::string& database) {
    try {
        unique_ptr<sql::Connection> con(get_driver_instance()->connect(server, username, password));
        con->setSchema(database);
        unique_ptr<sql::PreparedStatement> pstmt;
        pstmt.reset(con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)"));
        pstmt->setString(1, "banana");
        pstmt->setInt(2, 150);
        pstmt->execute();
        // ... 추가적인 데이터 삽입 ...
        cout << "Data insertion complete" << endl;
    }
    catch (sql::SQLException& e) {
        cout << "Error in insertData: " << e.what() << endl;
    }
}
