#include "IDatabase.h"
#include "Application.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock class for IDatabase
class MockDatabase : public IDatabase {
public:
    MOCK_METHOD(bool, Connect, (const std::string& connectionString), (override));
    MOCK_METHOD(bool, Disconnect, (), (override));
    MOCK_METHOD(std::string, Query, (const std::string& sql), (override));
};

// Test case using GoogleMock
TEST(ApplicationTest, FetchDataTest) {
    MockDatabase mockDatabase;

    // Set expectations
    EXPECT_CALL(mockDatabase, Connect("user=root;password=1234;"))
        .Times(1)
        .WillOnce(testing::Return(true));

    EXPECT_CALL(mockDatabase, Query("SELECT * FROM users"))
        .Times(1)
        .WillOnce(testing::Return("Mock query result"));

    EXPECT_CALL(mockDatabase, Disconnect())
        .Times(1);

    // Create Application object and inject the mock
    Application app(&mockDatabase);

    // Run
    std::string result = app.FetchData();
    EXPECT_EQ(result, "Mock query result");
}

TEST(ApplicationTest, FetchDataTest_cannotConnect) {

    // Set up
    MockDatabase mockDatabase;
    Application app(&mockDatabase);

    // Arrange
    EXPECT_CALL(mockDatabase, Connect("user=root;password=1234;"))
        .Times(1)
        .WillOnce(testing::Return(false));

    EXPECT_CALL(mockDatabase, Query("SELECT * FROM users"))
        .Times(0);

    EXPECT_CALL(mockDatabase, Disconnect())
        .Times(0);

    // Run
    std::string result = app.FetchData();

    // Assert
    EXPECT_EQ(result, "Connection failed.");
}

TEST(ApplicationTest, FetchDataTest_returnHello) {
    MockDatabase mockDatabase;

    // Set expectations
    EXPECT_CALL(mockDatabase, Connect("user=root;password=1234;"))
        .Times(1)
        .WillOnce(testing::Return(true));

    EXPECT_CALL(mockDatabase, Query("SELECT * FROM users"))
        .Times(1)
        .WillOnce(testing::Return("Hello"));

    EXPECT_CALL(mockDatabase, Disconnect())
        .Times(1);

    // Create Application object and inject the mock
    Application app(&mockDatabase);

    // Run
    std::string result = app.FetchData();
    EXPECT_EQ(result, "Hello");
}