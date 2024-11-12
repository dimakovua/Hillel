#include <iostream>


template<typename Derived>
class Base
{
public:
    void interface()
    {
        static_cast<Derived*>(this)->implementation();
    }

    void common()
    {
        std::cout << "Common\n";
    }

    int common2()
    {
        return 42;
    }
};

class Derived : public Base<Derived>
{
public:
    void implementation()
    {
        std::cout << "Implementation\n";
    }
};

class Aboba : public Base<Aboba>
{
public:
    void implementation()
    {
        std::cout << "Implementation Aboba\n";
    }
};


int main()
{
    Derived d;
    d.interface();
    d.common();
    std::cout << d.common2() << std::endl;


    Aboba a;
    a.interface();
    a.common();
    return 0;
}


class Base_virtual
{
public:
    virtual void interface() =0; 
};

class Derived_standard : public Base_virtual
{
    void interface() override
    {
        
    }
};