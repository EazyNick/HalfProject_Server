#ifndef DATAREAD_H
#define DATAREAD_H

#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <string>

void readDataFromDB(const std::string& server, const std::string& username, const std::string& password, const std::string& database);

#endif // DATAREAD_H
