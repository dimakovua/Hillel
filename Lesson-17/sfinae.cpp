#include <iostream>
#include <type_traits>
#include <concepts>
#include <vector>
#include <list>
#include <numeric>
//SFINAE - Substitution Failure Is Not An Error

template<typename Container>
auto average(const Container& container)
{
    using T = typename Container::value_type;
    T sum = std::accumulate(container.begin(), container.end(), T{});
    return static_cast<double>(sum) / container.size();
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::list<double> l = {1.1, 2.2, 3.3, 4.4, 5.5};

    std::cout << "Int vector: " << average(v) << std::endl;
    std::cout << "Double list: " << average(l) << std::endl;
    return 0;
}







template<typename... Args>
void print(Args... args)
{
    (std::cout << ... << args) << std::endl;
}



template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template<Number T>
T square(T value)
{
    return value * value;
}