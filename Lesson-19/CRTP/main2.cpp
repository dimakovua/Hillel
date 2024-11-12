#include <iostream>

template<typename Derived>
class Print
{
public:
    void printMethod()
    {
        std::cout << "Printing in the method of class: " << typeid(Derived).name() << "\n";
        static_cast<Derived*>(this)->method();
    }
};

class Class1 : public Print<Class1>
{
public:
    void method()
    {
        std::cout << "Method of Class1\n";
    }
};


class DataBase : public Print<DataBase>
{
public:
    void method()
    {
        std::cout << "Method of DataBase\n";
    }
};


template<typename Derived>
class Counter
{
    public:

    static int counter;

    void increment()
    {
        counter++;
    }

    void reportCount() const
    {
        std::cout << "Counter: " << counter << " in the " << typeid(Derived).name() <<"\n";
    }
};

template<typename Derived>
int Counter<Derived>::counter = 0;

class ExampleClass : public Counter<ExampleClass>
{
    public:
    void method()
    {
        increment();
        std::cout << "Method of ExampleClass\n";
    }
};

class ExampleClass1 : public Counter<ExampleClass1>
{
    public:
    void method()
    {
        increment();
        std::cout << "Method of ExampleClass1\n";
    }
};


int main()
{
    ExampleClass1 e1;
    ExampleClass e;

    for(int i = 0; i < 10; i++)
    {
        e1.method();
        e.method();
    }

    e.method();

    e.reportCount();
    e1.reportCount();
    return 0;
}