#ifndef DATADELETE_H
#define DATADELETE_H

#include <string>

void deleteDataFromDB(const std::string& server, const std::string& username,
    const std::string& password, const std::string& database);

#endif // DATADELETE_H
