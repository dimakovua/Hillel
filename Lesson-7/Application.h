#ifndef APPLICATION_H
#define APPLICATION_H

#include "IDatabase.h"

class Application {
public:
    // Constructor dependency injection
    Application(IDatabase* db) : database(db) {}

    // Setter dependency injection
    void SetDatabase(IDatabase* db) {
        database = db;
    }

    std::string FetchData() {
        if (database->Connect("user=root;password=1234;")) {
            std::string result = database->Query("SELECT * FROM users");
            database->Disconnect();
            return result;
        }
        return "Connection failed.";
    }

private:
    IDatabase* database;
};

#endif // APPLICATION_H
