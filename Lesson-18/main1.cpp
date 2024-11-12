#include <atomic>
#include <iostream>

std::atomic<int> x(0);

void writer()
{
    x.store(42);// запис
}

void reader()
{
    int y = x.load(); // читання
}

std::atomic<int> counter(0);

void increment()
{
    int old_value = counter.fetch_add(1); // збільшення на 1
}


std::atomic<int> value(0);

void change(int expected, int new_value)
{
    if(value.compare_exchange_strong(expected, new_value))
    {
        std::cout << "Value of atomic was == expected => we set new_value\n";
    }
}


std::atomic<int> k{0}, u{0};
std::atomic<int> z{0};

void thread1()
{
    k.store(1, std::memory_order_seq_cst);
}

void thread2()
{
    u.store(1, std::memory_order_seq_cst);
}

void thread3()
{
    if(k.load(std::memory_order_seq_cst) == 1 && u.load(std::memory_order_seq_cst) == 1)
    {
        z.store(1, std::memory_order_seq_cst);
    }
}