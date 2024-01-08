#ifndef DATAREAD_H
#define DATAREAD_H

#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <vector>

const std::string kDatabaseServer = "tcp://localhost:12333";
const std::string kDatabaseUsername = "root";
const std::string kDatabasePassword = "Password12#";

std::vector<std::string> readDataFromDB(const std::string& server, 
	const std::string& username, const std::string& password, const std::string& database);

#endif // DATAREAD_H
