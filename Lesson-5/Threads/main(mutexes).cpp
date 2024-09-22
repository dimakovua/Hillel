#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int counter = 0;
std::mutex mtx1, mtx2;

void thread1()
{
    std::lock(mtx1, mtx2);
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock); // waiting for mtx2 to be unlocked
    std::cout << "Thread 1 locked both mutexes\n";
} // unlock all the mutexes

void thread2()
{
    std::lock_guard<std::mutex> lock1(mtx1);
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::lock_guard<std::mutex> lock2(mtx2); // waiting for mtx1 to be unlocked
    std::cout << "Thread 2 locked both mutexes\n";
} // unlock all the mutexes

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}