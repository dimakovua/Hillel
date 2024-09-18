#include<iostream>

#include "MyMath.h"

/*Простой калькулятор, так как я "печенько" и не смог не чего придумать :(*/

int main()
{
    int val_1, val_2, x; //переменные для хранения значения и выбора в меню

    while (x != -1)
    {
        std::cout << "Welcome to the calculator! \n";
        std::cout << "Select an action: \n 1) Divide \n 2) Multiply \n 3) Square \n 4) Exit";
        std::cout << "Your choice: ";

        std::cin >> x;

        switch(x)
        {
            case 1:
                std::cout << "Enter the first value: ";
                std::cin >> val_1;

                std::cout << "Enter the second value ";
                std::cin >> val_2;

                Math::divide(val_1, val_2);
                break;
            case 2:
                std::cout << "Enter the first value: ";
                std::cin >> val_1;

                std::cout << "Enter the second value ";
                std::cin >> val_2;

                Math::multiply(val_1, val_2);
                break;
            case 3:
                std::cout << "Enter the number: ";
                std::cin >> val_1;

                std::cout << "Enter the degree value ";
                std::cin >> val_2;

                Math::square(val_1, val_2);
                break;
            case 4:
                x = -1;
                break;
        }
    }
    

}
