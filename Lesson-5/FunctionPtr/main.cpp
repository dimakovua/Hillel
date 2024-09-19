#include <iostream>
#include <string>
#include <vector>

void Print_inc(int a)
{
    a++;
    std::cout << "Value++: " << a << "\n";
}

void Print(int a)
{
    std::cout << "Value: " << a << "\n";
}

void iterate_and_exec(std::vector<int>& vec, void(*param_func)(int))
{
    for(auto i : vec)
    {
        param_func(i);
    }
}

int main()
{
    std::vector<int> vec = {1, 2, 3, 4};
    iterate_and_exec(vec, Print);
    iterate_and_exec(vec, Print_inc);
    iterate_and_exec(vec, [](int a) { std::cout << "Lambda!\n"; });
    

}