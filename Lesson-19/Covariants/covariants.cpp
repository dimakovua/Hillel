#include <iostream>

class Animal
{
public:
    virtual Animal* create() const
    {
        return new Animal();
    }

    virtual void speak() const
    {
        std::cout << "Animal speaks\n";
    }
};

class Dog : public Animal
{
public:
    Dog* create() const override
    {
        return new Dog();
    }

    void speak() const override
    {
        std::cout << "Woof!\n";
    }
};

void makeHimSpeak(const Animal& a)
{
    Animal* newAnimal = a.create();
    newAnimal->speak();
    delete newAnimal;
}

int main()
{
    Dog d;
    makeHimSpeak(d);
    return 0;
}