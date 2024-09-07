#include <iostream>
#include "stack.h"

int main()
{
    Stack<int,4> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5); // err -> stack overflow
    std::cout << stack.top() << std::endl; // -> 4
    stack.pop();
    stack.pop();
    stack.pop();
    std::cout << stack.top() << std::endl; // -> 1
    stack.pop();
    stack.pop();



    return 0;
}

