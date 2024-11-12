#include <iostream>
#include <chrono>
#include <thread>

template<typename Derived>
class Seconds
{
    public:
    void execAndTimed()
    {
        auto start = std::chrono::high_resolution_clock::now();
        static_cast<Derived*>(this)->exec();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        std::cout << "For method of " << typeid(Derived).name() << " elapsed time: " << duration.count() << " seconds\n";
    }
};

class Class1 : public Seconds<Class1>
{
    public:
    void exec()
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        for(int i = 0; i < 1000000; i++)
        {
            i++;
        }
        std::cout << "Executed method of Class1\n";
    }
};

class Class2 : public Seconds<Class2>
{
    public:
    void exec()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for(int i = 0; i < 1000000; i++)
        {
            i++;
        }
        std::cout << "Executed method of Class2\n";
    }
};

int main()
{
    Class1 c1;
    c1.execAndTimed();

    Class2 c2;
    c2.execAndTimed();
    return 0;
}