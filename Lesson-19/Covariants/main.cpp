#include <iostream>
#include <thread>
class Shape
{
public:
    virtual void draw() const =0 ;
    virtual ~Shape() = default;
};

class Circle : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing a circle\n";
    }
};

class Square : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing a square\n";
    }
};

class Aboba
{
public:
    void draw() const
    {
        std::cout << "Drawing an Aboba\n";
    }
};

template<typename T>
void renderAndDraw(const T& s)
{
    static_assert(std::is_base_of<Shape, T>::value, "T must be derived from Shape");
    std::cout << "Rendering";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::cout << ".";
    std::cout << "Done!\n";
    s.draw();
}

int main()
{
    Circle c;
    Aboba a;
    Square s;

    renderAndDraw(c);
    renderAndDraw(s);
    renderAndDraw(a);
    return 0;
}