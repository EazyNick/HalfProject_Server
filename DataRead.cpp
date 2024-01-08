#include "DataRead.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <iostream>
#include <sstream>

using namespace std;

std::vector<std::string> readDataFromDB(const string& server, const string& username, const string& password, const string& database) {
    sql::Driver* driver; // �����ͺ��̽� ����̹�
    sql::Connection* con; // Ŀ����
    sql::PreparedStatement* pstmt; // �غ�� ��ɹ�
    sql::ResultSet* result; // ��� ����
    std::vector<std::string> rows; // rows�� ���� ����� ������ ����
    ostringstream oss; // oss�� ���ڿ� ��Ʈ��(�������� �������� �帧)

    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema(database);

        pstmt = con->prepareStatement("SELECT * FROM inventory;");
        result = pstmt->executeQuery();

        while (result->next()) {
            printf("Reading from table=(%d, %s, %d)\n", result->getInt(1), result->getString(2).c_str(), result->getInt(3));
            oss.str(""); // ��Ʈ���� ���ϴ�. �� ���ڿ��� ����.
            oss << "Reading from table=(" << result->getInt(1) << ", " << result->getString(2) << 
                ", " << result->getInt(3) << ")" << '\0';
            
            // ��� ������ �ݺ��ϸ鼭 �� ���� �а�, 
            // �̸� std::ostringstream�� �������Ͽ� ���ڿ��� ��ȯ�� ���� rows ���Ϳ� �߰�
            rows.push_back(oss.str());
        }

        delete result;
        delete pstmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        rows.clear();
        rows.push_back("Error");
    }

    return rows;
    /* rows ���� ���� ����
     "Reading from table=(1, Apple, 100)"
     "Reading from table=(2, Banana, 200)"
     "Reading from table=(3, Cherry, 300)"
     */
    
}
