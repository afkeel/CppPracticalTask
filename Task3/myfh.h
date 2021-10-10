#ifndef MYFH_H
#define MYFH_H
#include <iostream>

const int kilometer{ 1000 };
const int minute{ 60 };
const int hour{ minute * 60 };

template<typename T>
T enter_val(const char* str)
{
	T val{};
	do
	{
		std::cout << str;
		std::cin >> val;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Ошибка ввода!\n";
		}
		else
		{
			std::cin.ignore(32767, '\n');
			break;
		}
	} while (true);
	return val;
}
#endif

