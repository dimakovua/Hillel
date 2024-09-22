#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <numeric>
#include <mutex>

void partialSum(const std::vector<int>& vec, long long& result, size_t start, size_t end) {
    result = std::accumulate(vec.begin() + start, vec.begin() + end, 0LL);
}

int main()
{
    std::vector<int> vec(1'000'000'000, 5);

    long long result1 = 0, result2 = 0, result3 = 0;
    size_t vec_size = vec.size();
    size_t border = vec_size / 3;
    size_t border2 = border + border;
    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(partialSum, std::cref(vec), std::ref(result1), 0, border);
    std::thread t2(partialSum, std::cref(vec), std::ref(result2), border, border2);
    std::thread t3(partialSum, std::cref(vec), std::ref(result3), border2, vec_size);

    
    t1.join();
    t2.join();

    long long result = result1 + result2 + result3;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Sum: " << result << "\n";
    std::cout << "Duration: " << elapsed.count() << "\n";

} // 0.77