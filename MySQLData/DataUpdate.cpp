#include "DataUpdate.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <iostream>

void updateDataInDB(const string& server, const string& username, const string& password, const string& database) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    try {
        driver = get_driver_instance(); // Retrieves a new instance of the SQL driver(DB�� ��ȣ�ۿ� �ϰ� ���ִ� ��)
        con = driver->connect(server, username, password); // connection to the database server
        con->setSchema(database); // Selects the given database to work with

        pstmt = con->prepareStatement("UPDATE inventory SET quantity = ? WHERE name = ?");
        pstmt->setInt(1, 200); // 1���� ?�� 200 ���� ����.
        pstmt->setString(2, "banana"); // 2���� ?�� banana�� ����
        pstmt->executeQuery(); // Executes the prepared SQL query
        cout << "Row updated\n";

        delete pstmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
