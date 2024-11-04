#include <iostream>
#include <ranges>

class CStringIterator
{
public:
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using iterator_category = std::forward_iterator_tag;

    CStringIterator(char* ptr) : ptr(ptr) {}

    reference operator*() const { return *ptr; }
    CStringIterator& operator++() { ++ptr; return *this; }
    bool operator==(const CStringIterator& other) const { return ptr == other.ptr; }
    bool operator!=(const CStringIterator& other) const { return ptr != other.ptr; }

    const char* getPtr() const { return ptr; }

private:
    char* ptr;
};

class CStringSentinel {};

bool operator==(const CStringIterator& it, const CStringSentinel&) { return *it.getPtr() == '\0'; }
bool operator!=(const CStringIterator& it, const CStringSentinel&) { return *it.getPtr() != '\0'; }

int main()
{
    const char* str = "Hello, World!";

    CStringIterator begin(const_cast<char*>(str));
    CStringSentinel end;

    for(auto it = begin; it != end; ++it)
    {
        std::cout << *it;
    }
    std::cout << "\n";
}