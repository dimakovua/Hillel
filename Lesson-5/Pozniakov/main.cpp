#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cmath>

std::mutex mtx;
int sum = 0;



void thread_func(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    for(auto i = begin;i != end; ++i)
    {
        int value = std::pow(*i,2);
        *i = value;
        {
            std::lock_guard<std::mutex> lock(mtx);
            sum += value;
        }
    }
}


int main()
{
    std::vector<int> vector(1000, 5);

    auto middle_iter = vector.begin() + vector.size() / 2;

    std::thread thread1(thread_func,vector.begin(),middle_iter);
    std::thread thread2(thread_func,middle_iter,vector.end());

    thread1.join();
    thread2.join();

    std::cout << sum << std::endl; // -> 25000

}