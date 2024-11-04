//forward iterator
//random access iterator
//bidirectional iterator

// ++it
// --it

// *it
// it1 == it2  it1 != it2

// Random Access Iterator
// it + n
// it - n
// it[n]

#include <iostream>
#include <vector>
#include <list>
#include <numeric>


class NumberList
{
public:
    NumberList(std::initializer_list<int> list) : numbers(list) {}

    class Iterator
    {
    public:
        Iterator(int* ptr) : ptr(ptr) {}

        int& operator*() { return *ptr; }
        Iterator operator++() { ++ptr; return *this; }
        Iterator operator--() { --ptr; return *this; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

    private:
        int* ptr;
    };

    Iterator begin() { return Iterator(numbers.data()); }
    Iterator end() { return Iterator(numbers.data() + numbers.size()); }
    
private:
    std::vector<int> numbers;
};


int main()
{

    NumberList list = {1, 2, 3, 4, 5};
    NumberList::Iterator it = list.begin();
    ++it;
    ++it;
    std::cout << "!!! " << *it << std::endl;
    for(auto element : list)
    {
        std::cout << element << " ";
    }



    // std::vector<int> v = {1, 2, 3, 4, 5};
    // std::list<int> l = {1, 2, 3, 4, 5};
    // std::list<int>::const_iterator it = l.begin();
    // it = l.end();
    // it++;
    // it--;

    //std::accumulate(l.begin(), l.end(), 0);
    
    // for(auto element : l)
    // {
    //     //std::cout << element << " ";
    // }

    // for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    // {
    //    // std::cout << *it << " ";
    // }

    // for(std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
    // {
    //   //  std::cout << *it << " ";
    // }


}
