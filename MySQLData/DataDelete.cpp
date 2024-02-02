// DataDelete.cpp
#include "DataDelete.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>

void deleteDataFromDB(const std::string& server, const std::string& username,
    const std::string& password, const std::string& database) {
    try {
        sql::Driver* driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema(database);
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("DELETE FROM inventory WHERE name = ?"));
        pstmt->setString(1, "orange");
        pstmt->executeUpdate();
        std::cout << "Row deleted\n";
    }
    catch (sql::SQLException& e) {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
    }
}
