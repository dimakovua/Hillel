#include <gtest/gtest.h>

class Math
{
    public:
    int Multiply(int a, int b) { return a * b; }
    int Divide(int a, int b) { 
        if (b == 0) throw std::invalid_argument("Divide by zero");
        return a / b;
    }
};

class MathTest : public ::testing::Test
{
    protected:
    Math* m = nullptr;

    void SetUp() override
    {
        m = new Math();
    }

    void TearDown() override
    {
        delete m;
    }
};


TEST_F(MathTest, TestMultiply)
{
    EXPECT_EQ(m->Multiply(1, 1), 1);
}

TEST_F(MathTest, TestMultiply_returnZero)
{
    EXPECT_EQ(m->Multiply(1, 0), 0);
}

TEST_F(MathTest, TestDivideByZero_throwsException)
{
    // Run & Assert
    EXPECT_THROW(m->Divide(5, 0), std::invalid_argument);
}

TEST_F(MathTest, TestDefault)
{
    // Set up
    
    
    // Arrange

    // Run & Assert

    // Clean up (delete, SetImpl(nullptr) ...)
}