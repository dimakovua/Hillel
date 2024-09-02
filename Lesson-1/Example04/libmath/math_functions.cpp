#include "math_functions.h"

int Math::add(int a, int b)
{
    return a + b;
}

int Math::divide(int a, int b)
{
    if(b != 0)
        return a / b;
    
    return -1;
}