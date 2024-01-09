// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <string>

using namespace std;

// 함수 선언
void initializeDatabase(const std::string& server, const std::string& username, const std::string& password, const std::string& database);
void createTable(const std::string& server, const std::string& username, const std::string& password, const std::string& database);
void insertData(const std::string& server, const std::string& username, const std::string& password, const std::string& database);

#endif // DATABASE_H

