/*
#include <iostream>
#include <cstddef>

struct A{
    char c;
    int i;
    char c2;
};


int main()
{
    std::cout << "Align of A: " << alignof(A) << std::endl;
    std::cout << "Offset c " << offsetof(A, c) << std::endl;
    std::cout << "Offset i " << offsetof(A, i) << std::endl;
    std::cout << "Offset c2 " << offsetof(A, c2) << std::endl;
    return 0;
}
*/

#include <iostream>
#include <string>
#include <new>
#include <vector.h>

struct Student
{
    std::string Name;
    double Rating;

    void Print() const
    {
        std::cout << "My name is " << Name << " i have  " << Rating << std::endl;
    }
};


int main()
{
    { // On stack
        Student s{"Oleksandr", 5.0};
        s.Print();
    }
    { // Heap
        Student * s = new Student{"Sasha", 5.1}; // allocate raw memory + placement new
        s->Print();
        delete s;
    }
    {
        alignas(Student) char buf[1024]; // RAW MEMORY on stack
        Student * s = new (buf) Student{"Sashko", 6.0}; // Placement new
        s->Print();
    }
    {
        void * buf = operator new(sizeof(Student)); // RAW MEMORY on heap
        Student * s = new (buf) Student{"Shura", 7.0};
        // 
        s->Print();
        s->~Student();
        operator delete(buf);
    }
    {
        Student s;
        s.~Student();
        new (&s) Student{"Alex", 235.5};
        s.Print();
    }
}

// 