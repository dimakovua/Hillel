#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx; 
int chicken_count = 0; 
int egg_count = 0; 

void run(const std::string& message, int& counter) {
    for (int i = 0; i < 10; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        
        counter++;
        
        std::cout << message << " " << counter << std::endl;
    }
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(run, "Chicken", std::ref(chicken_count));
    }

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(run, "Egg", std::ref(egg_count));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
