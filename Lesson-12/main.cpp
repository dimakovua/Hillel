#include <iostream>
#include <future>
#include <vector>
#include <numeric>

long long sumOfSquares(const std::vector<int>& numbers, size_t start, size_t end)
{
    long long sum = 0;
    for(size_t i = start; i < end; i++)
    {
        sum += static_cast<long long>(numbers[i]) * numbers[i];
    }

    return sum;
}

int main()
{
    std::vector<int> numbers(1000000);

    std::iota(numbers.begin(), numbers.end(), 1);

    int numTasks = 8;
    size_t partSize = numbers.size() / static_cast<size_t>(numTasks);

    std::vector<std::future<long long>> futures;

    for(int i = 0; i < numTasks; ++i)
    {
        size_t start = static_cast<size_t>(i) * partSize;

        size_t end = (i == numTasks - 1) ? numbers.size() : start + partSize; 
        futures.push_back(std::async(std::launch::async, sumOfSquares, std::ref(numbers), start, end));
    }

    long long totalSum = 0;

    for(auto& future : futures)
    {
        totalSum += future.get();
    }

    std::cout << "Result: " << totalSum << "\n";

    return 0;
}