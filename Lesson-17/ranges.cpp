
#include <vector>
#include <iostream>
#include <ranges>

int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto evenNumbers = numbers | std::ranges::views::filter([](int n){ return n % 2 == 0; }) 
                               | std::ranges::views::transform([](int n) { return n * 2; })
                               | std::ranges::views::take(3)
                               | std::ranges::views::drop(1);



    for(int n : evenNumbers)
    {
        std::cout << n << " ";
    }
}