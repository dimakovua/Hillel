#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void print_numbers(int start) {
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = start; i < start + 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::thread t1(print_numbers, 1);
    std::thread t2(print_numbers, 6);

    t1.join();
    t2.join();

    return 0;
}
