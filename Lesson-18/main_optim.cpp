
#include <iostream>

int add(int x, int y) {
    return x + y;
}

int main() {
    int a = 5;
    int b = 10;
    int result = add(a, b);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
