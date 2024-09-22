#include<iostream>
#include "OneWayList.h"

int main()
{
	OneWayList<int,float> test;
	test.Add(2);
	test.Add(3);
    	for (unsigned int i = 0; i < test.Size(); ++i)
	{
		std::cout << "Elem #" << i  << "\n";
	}
	return 0;
}
