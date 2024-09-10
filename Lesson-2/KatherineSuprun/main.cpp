#include <iostream>
#include "vector.h"

int main() {
    MyTemplateClass<int> intVector;
    intVector.addElement(10);
    intVector.addElement(20);
    intVector.addElement(30);

    std::cout << "Initial vector of integers:" << std::endl;
    intVector.printElements();

    std::cout << "Size of vector: " << intVector.getSize() << std::endl;

    intVector.removeLastElement();
    std::cout << "After removing the last element:" << std::endl;
    intVector.printElements();

    try {
        std::cout << "Element at index 1: " << intVector.getElementAt(1) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    MyTemplateClass<std::string> stringVector;
    stringVector.addElement("Hello");
    stringVector.addElement("World");
    stringVector.addElement("!");

    std::cout << "Vector of strings:" << std::endl;
    stringVector.printElements();

    return 0;
}
