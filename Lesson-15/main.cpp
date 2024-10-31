#include <memory>
#include <vector>
#include <iostream>

int main()
{
    // std::vector<int> source = {1, 2, 3, 4, 5, 6, 7, 8};

    // int* dest = static_cast<int*>(operator new(source.size() * sizeof(int)));

    // std::uninitialized_copy_n(source.begin(), 3, dest);

    // for(size_t i = 0; i < 3; ++i)
    // {
    //     std::cout << dest[i] << " ";
    // }
    // std::cout << "\n";

    // std::destroy(dest, dest + 3);
    // operator delete(dest);

    size_t n = 5;
    int* dest = static_cast<int*>(operator new(n * sizeof(int)));

    std::uninitialized_fill(dest, dest + n, 42);

    for(size_t i = 0; i < n; ++i)
    {
        std::cout << dest[i] << " ";
    }
    std::cout << "\n";

    std::destroy(dest, dest + n);
    operator delete(dest);

    return 0;
}