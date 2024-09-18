#include <vector>
#include <iostream>
#include <memory>
template<typename T>
class MyStack
{
private:
    std::vector<T> stack;

public:
    void push(T value)
    {
        stack.push_back(value);
    }

    void pop()
    {
        
        if(!stack.empty())
            stack.pop_back();
        else
            std::cout << "Nothing to pop! Stack is empty!\n";
    }

    T top() const
    {
        if(!stack.empty())
            return stack.back();
        else
        {
            std::unique_ptr<int> aboba = std::make_unique<int>(5);
            std::cout << "Stack is empty!\n";
            return T();
        }
    }

    bool isEmpty() const
    {
        return stack.empty();
    }
};