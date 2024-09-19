/*моля либа с шаблоными функциями для калькулятора*/
#pragma one

template<class T>
class Math
{
public:
    /*Функция деления. На вход принимает два целых числа.*/
    static T divide (T a, T b)
    {
        if (b != 0){
        return a / b;
        }
        else{
            return -1;
        } 
    }
    /*Функция умножение. На вход принимает два целых числа.*/
    static T multiply(T a, T b)
    {
        return a * b;
    }
    /*Функция возведения в степень. Первый параметр целое число, второй степень в которую возвадим.*/
    static T square (T a, T b)
    {
        int res = 0;

        for(int i = 0; i <= b; i++)
        {
            res *= a;
        }

        return res;
    }
};