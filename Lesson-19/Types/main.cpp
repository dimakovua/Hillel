#include <type_traits>
#include <iostream>

template<typename T>
T square(T value)
{
    static_assert(std::is_arithmetic<T>::value, "The type must be arithmetic");
    return value * value;
}

template<typename T, typename = std::void_t<>>
struct has_serialize : std::false_type {};

template<typename T>
struct has_serialize<T, std::void_t<decltype(std::declval<T>().serialize())>> : std::true_type {};


template<typename C>
void process(const C& obj)
{
    static_assert(std::is_copy_constructible<C>::valiue, "The type must be copy constructible");
    std::cout << "Processing\n";
}

class A
{
    public:
    void serialize() const
    {
        std::cout << "Serializing A\n";
    }
};

class B
{
    public:
    void print()
    {
        std::cout << "B\n";
    }
};

template<typename T>
void save(const T& obj)
{
    if constexpr(has_serialize<T>::value) 
    {
        obj.serialize();
    }
    else
    {
        std::cout << "No serialize method\n";
    }
}




int main()
{
    A a;
    B b;
    save(a);
    save(b);
    return 0;
}