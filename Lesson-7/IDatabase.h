#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>

class IDatabase {
public:
    virtual ~IDatabase() {}

    virtual bool Connect(const std::string& connectionString) = 0;
    virtual bool Disconnect() = 0;
    virtual std::string Query(const std::string& sql) = 0;
};

#endif // IDATABASE_H
