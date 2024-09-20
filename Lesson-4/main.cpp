#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void egg() {
    
    std::lock_guard<std::mutex> lock (mtx);
    std::cout << "Egg!" << std::endl;
}

void chicken() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Chicken!" << std::endl;
}

int main() {
    
    std::thread t1(egg);
    std::thread t2(chicken);

    t1.join();
    t2.join();

    return 0;

}


