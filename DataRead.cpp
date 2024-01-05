#include "DataRead.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <iostream>

using namespace std;

void readDataFromDB(const string& server, const string& username, const string& password, const string& database) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* result;

    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema(database);

        pstmt = con->prepareStatement("SELECT * FROM inventory;");
        result = pstmt->executeQuery();

        while (result->next()) {
            printf("Reading from table=(%d, %s, %d)\n", result->getInt(1), result->getString(2).c_str(), result->getInt(3));
        }

        delete result;
        delete pstmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
    }
}
