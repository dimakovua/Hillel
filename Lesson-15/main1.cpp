#include <string>
#include <utility>
#include <iostream>
#include <vector>

class MyString
{
private:
    char* data;
    size_t length;

public:
    MyString(const char* str) : length(strlen(str)), data(new char[length + 1])
    {
        strcpy(data, str);
    }

    MyString(const MyString& other) : length(other.length), data(new char[length + 1])
    {
        strcpy(data, other.data);
    }
    // lvalue === T&
    // rvalue === T&&
    MyString(MyString&& other) noexcept : data(other.data), length(other.length)
    {
        other.data = nullptr;
        other.length = 0;
        std::cout << "Move constructor called!\n";
    }

    MyString& operator=(MyString&& other) noexcept
    {
        if(this != &other)
        {
            delete[] data; // delete our old data
            data = other.data;
            length = other.length;

            other.data = nullptr;
            other.length = 0;

            std::cout << "Move assignment operator called!\n";
        }

        return *this;
    }

    ~MyString()
    {
        delete[] data;
    }

    void print() const
    {
        if(data) std::cout << data << "\n";
        else std::cout << "EMPTY\n";
    }
};



void print(int& x)
{
    std::cout << "LVALUE: " << x << std::endl;
}

void print(int&& x)
{
    std::cout << "RVALUE: " << x << std::endl;
}

template<typename T>
void wrapper(T&& arg)
{
    print(std::forward<T>(arg));
}


int main()
{
    int a = 10;
    wrapper(a);
    wrapper(20);











MyString obj("hello");
MyString obj2 = std::move(obj); // obj is MyString&& type

obj.print();
obj2.print();


// int i = 5;

// bool b = true;
// int *i = nullptr;
// std::string str = "hello"; // str is lvalue
// std::string str1 = std::move(str); // std::move makes str xvalue

// std::cout << str1; // hello
// std::cout << str; // ? empty; 

// HERE
    
                    // expression
    
         // gvalue(T&, T)           // rvalue (T&&)
        //    //             //         //
      //       //           //             //
    //lvalue    xvalue (expiring value)      prvalue (pure rvalue)
}