#ifndef DBCONFIG_H
#define DBCONFIG_H

#include <string>

class DBConfig {
public:
    DBConfig(const std::string& server, const std::string& user,
        const std::string& pwd, const std::string& db)
        : server_(server), username_(user), password_(pwd), database_(db) {}

    const std::string& GetServer() const { return server_; }
    const std::string& GetUsername() const { return username_; }
    const std::string& GetPassword() const { return password_; }
    const std::string& GetDatabase() const { return database_; }

private:
    std::string server_;
    std::string username_;
    std::string password_;
    std::string database_;
};

#endif // DBCONFIG_H
