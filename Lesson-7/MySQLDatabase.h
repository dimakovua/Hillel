#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include "IDatabase.h"
#include <iostream>

class MySQLDatabase : public IDatabase {
public:
    bool Connect(const std::string& connectionString) override {
        std::cout << "Connecting to MySQL database with connection string: " << connectionString << std::endl;
        return true;
    }

    bool Disconnect() override {
        std::cout << "Disconnecting from MySQL database." << std::endl;
        return true;
    }

    std::string Query(const std::string& sql) override {
        std::cout << "Executing SQL query: " << sql << std::endl;
        return "Query result from MySQL database.";
    }
};

#endif // MYSQLDATABASE_H
