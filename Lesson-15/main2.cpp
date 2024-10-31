#include <stdexcept>


class A
{
public:
    int* i;
    A()
    {
        i = new int(5);
    }

    ~A()
    {
        delete i;

        throw(std::runtime_error("error"));
    }
};


void g()
{
    A b();
    A a();
    throw std::runtime_error("lol");
    //
}

void f()
{
    bool b;
    bool j;
    g();
}

int main() {
    int b;
    int a;
    try{
        f();
    }catch(...)
    {

    }

    return 0;
}

// EXCEPTION!!!!!!
// A a() --destroyed THROW EXCEPTION
// A b() --destroyed THROW EXCEPTION
// g()
// bool j --destroyed
// bool b --destroyed
// f()
// int a --destroyed
// int b --destroyed
// catch