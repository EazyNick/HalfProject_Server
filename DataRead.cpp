#include "DataRead.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <iostream>
#include <sstream>

using namespace std;

std::vector<std::string> readDataFromDB(const string& server, const string& username, const string& password, const string& database) {
    sql::Driver* driver; // 데이터베이스 드라이버
    sql::Connection* con; // 커넥터
    sql::PreparedStatement* pstmt; // 준비된 명령문
    sql::ResultSet* result; // 결과 집합
    std::vector<std::string> rows; // rows는 쿼리 결과를 저장할 벡터
    ostringstream oss; // oss는 문자열 스트림(데이터의 연속적인 흐름)

    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema(database);

        pstmt = con->prepareStatement("SELECT * FROM inventory;");
        result = pstmt->executeQuery();

        while (result->next()) {
            printf("Reading from table=(%d, %s, %d)\n", result->getInt(1), result->getString(2).c_str(), result->getInt(3));
            oss.str(""); // 스트림을 비웁니다. 빈 문자열로 만듬.
            oss << "Reading from table=(" << result->getInt(1) << ", " << result->getString(2) << 
                ", " << result->getInt(3) << ")" << '\0';
            
            // 결과 집합을 반복하면서 각 행을 읽고, 
            // 이를 std::ostringstream에 포맷팅하여 문자열로 변환한 다음 rows 벡터에 추가
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
    /* rows 저장 형태 예시
     "Reading from table=(1, Apple, 100)"
     "Reading from table=(2, Banana, 200)"
     "Reading from table=(3, Cherry, 300)"
     */
    
}
