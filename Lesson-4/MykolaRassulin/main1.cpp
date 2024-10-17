#include <iostream>



class Shape {
public:
    virtual int area() const = 0; // Pure virtual function
    virtual ~Shape() = default;

};

class Rectangle : public Shape {

public:
    Rectangle(int width, int height) : m_width(width), m_height(height) {}

    int getWidth() const {
        return m_width;
    }

    int getHeight() const {
        return m_height;
    }

    void setWidth(int width) {
        m_width = width;
    }

    void setHeight(int height) {
        m_height = height;
    }

    int area() const override {
        return m_width * m_height;
    }

private:
    int m_width;
    int m_height;
};

class Square : public Shape {
public:
    Square(int side) : m_side(side) {}

    void setSide(int side) {
        m_side = side;
    }

    int getSide() const {
        return m_side;
    }

    int area() const override {
        return m_side * m_side;
    }

private:
    int m_side;
};

void printArea(const Shape& shape) {
    std::cout << "Area: " << shape.area() << std::endl;
}

int main() {
    Rectangle rect(5, 10);
    Square square(5);

    printArea(rect);    // Outputs: Area: 50
    printArea(square);  // Outputs: Area: 25

    return 0;
}

//S.O.L.I.D
// S - Single Responsibility Principle
// O - open closed principle
// L - Liskov Principle
// I - interface segregation
// D - dependency inversion
