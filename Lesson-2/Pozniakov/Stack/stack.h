#pragma once
#include <iostream>
#include <exception>

//fixed size stack
template<class T, std::size_t stack_capacity>
class Stack
{
    T _data[stack_capacity] = {};
    std::size_t _capacity = stack_capacity;
    std::size_t _size = 0;

public:

    Stack() : _size(0) {};

    Stack(const T& value)
    {
        _data[_size++] = value;
    };

    void push(const T& value)
    {
        if(_size == _capacity)
        {
            std::cerr << "Stack overflow!" << std::endl;
            return;
        }
        _data[_size++] = value;
    }

    void pop()
    {
        if(_size == 0) return;
        --_size;
    }

    T top()
    {
        if(_size == 0) return {};
        return _data[_size - 1];
    }

    std::size_t size()
    {
        return _size;
    }

};