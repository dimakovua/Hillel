#include <iostream>
#include <thread>
#include <atomic>

std::atomic<size_t> counter(0);
size_t bad_counter = 0;

void increment(int times)
{
    for(int i = 0; i < times; ++i)
    {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

void bad_increment(int times)
{
    for(int i = 0; i < times; ++i)
    {
        bad_counter++;
    }
}

int main()
{
    std::thread t1(bad_increment, 1000000);
    std::thread t2(bad_increment, 1000000);

    t1.join();
    t2.join();

    std::cout << "Counter: " << bad_counter << std::endl;
}