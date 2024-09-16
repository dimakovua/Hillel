#include <iostream>
#include <string>

#include "myStack.h"

template <typename T, typename U>
class Pair {
public:
    void print() {
        std::cout << "General Pair" << std::endl;
    }
};

template <typename T>
class Pair<T, int> {
public:
    void print() {
        std::cout << "Partial Specialization with int" << std::endl;
    }
};

int main()
{
    Pair<double, double> p1;
    Pair<int, double> p2;
    Pair<double, int> p3;

    p1.print();
    p2.print();
    p3.print();
}

