#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

int main()
{
    std::vector<int> numbers = {1, 2, 5, 3, 8, 1};

    std::sort(numbers.begin(), numbers.end(), [](int a, int b){
        return a < b;
    });

    for(auto it : numbers)
    {
        std::cout << it << "\t";
    }

}