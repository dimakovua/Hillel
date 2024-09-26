#include <iostream>

#include "MyClass.h"
namespace
{

    constexpr int PI_NUMBER = 31415;

    constexpr int square(int x)
    {
        return x * x;
    }

    int doSmallerWork()
    {

    }

    int print() noexcept
    {
        std::cout << "HEllo!\n";
    }

    void parse()
    {

    }
};

void MyClass::doHardWork()
{s
    try{
        doSmallerWork();
        parse();
    }
    print();
}