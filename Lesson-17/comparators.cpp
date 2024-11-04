#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>


operator <=>

void sortStrings(std::vector<std::string>& strings, bool ascending)
{
    if(ascending)
    {
        std::sort(strings.begin(), strings.end());
    }
    else
    {
        std::sort(strings.begin(), strings.end(), std::greater<std::string>());
    }
}


// class (functor)
class LengthComparator
{
public:
    bool operator()(const std::string& a, const std::string& b) const
    {
        return a.size() > b.size();
    }

};

// comparator as function
bool reverseAlphabetical(const std::string& a, const std::string& b)
{
    return a > b;
}

int main()
{

    std::set<int, std::greater<int>> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 

    for(const auto& number : numbers)
    {
        std::cout << number << " ";
    }



    //std::vector<std::string> words = {"aa", "bbbbbbbbb", "cdd", "d", "tewdfe"};
    //std::sort(words.begin(), words.end(), reverseAlphabetical);
    //std::sort(words.begin(), words.end(), LengthComparator());

    // std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b)
    // {
    //     return a.size() > b.size();
    // });

    // for(const auto& word : words)
    // {
    //     std::cout << word << " ";
    // }

    return 0;
}