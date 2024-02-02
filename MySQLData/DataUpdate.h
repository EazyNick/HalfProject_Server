#ifndef DATAUPDATE_H
#define DATAUPDATE_H

#include <string>

using namespace std;

void updateDataInDB(const std::string& server, 
	const std::string& username, const std::string& password, const std::string& database);

#endif // DATAUPDATE_H