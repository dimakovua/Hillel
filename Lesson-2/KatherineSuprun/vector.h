#pragma once

#include <iostream>
#include <vector>

template <typename T>
class MyTemplateClass {
private:
    std::vector<T> elements;
public:
    void addElement(T element) {
        elements.push_back(element);
    }

    void removeLastElement() {
        if (!elements.empty()) {
            elements.pop_back();
        } else {
            std::cout << "Vector is empty, nothing to remove!" << std::endl;
        }
    }

    size_t getSize() const {
        return elements.size();
    }

    T getElementAt(size_t index) const {
        if (index < elements.size()) {
            return elements[index];
        } else {
            throw std::out_of_range("Index out of bounds!");
        }
    }

    void printElements() const {
        if (elements.empty()) {
            std::cout << "No elements in the vector." << std::endl;
        } else {
            std::cout << "Elements in the vector: ";
            for (const auto& el : elements) {
                std::cout << el << " ";
            }
            std::cout << std::endl;
        }
    }
};
