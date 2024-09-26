#include <iostream>
#include <vector>
#include <algorithm>

size_t counter = 0;

class MyClass
{
    public:
    void Print() const
    {
        std::cout << ":)\n";
    }
};

void printWithIndex(const MyClass& c)
{
    std::cout << "Class number " << counter << " said ";
    counter++;
    c.Print();
}

int main()
{
    std::vector<int> vec = {12, 1, 3, 3, 4, 4, 5, 8, 9, 12, 11, 12, 13};

    vec.erase(std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; } ), vec.end()); 

    std::cout << "After removal: ";
    for (int i : vec) 
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
}