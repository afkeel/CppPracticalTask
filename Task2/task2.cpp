#include <iostream>
#include <random>
#include <ctime>
#include <array>

double calcCost(double d, double rg, double eg)
{
	return d * eg / 100 * rg;
}

double calcDisc(double s, int d)
{
	s -= s * d / 100;;
	return s;
}

int getRdInt(int min, int max)
{
	//static std::mt19937 mers{ std::random_device {}() };
	static std::mt19937 mers{ static_cast<unsigned int>(time(0))};
	return std::uniform_int_distribution { min, max } (mers);
}

void getArr(std::array <int, 3> &m, int x)
{	
	for (size_t i = m.size(); i != 0; i--)
	{
		m.at(i-1) = x % 10;
		x /= 10;
	}
} 

int main()
{
	setlocale(0, "");

	/*Напишите программу вычисления стоимости поездки на автомобиле на дачу(туда и обратно).*/

	/*double dist, rate_gas, exp_gas;
	double cost;
	std::cout << "Расстояние до дачи (км): ";
	std::cin >> dist;
	std::cout << "Расход бензина (литров на 100 км пробега): ";
	std::cin >> exp_gas;
	std::cout << "Цена литра бензина (руб.): ";
	std::cin >> rate_gas;
	cost = 2 * calcCost(dist, rate_gas, exp_gas);
	std::cout << "Поездка на дачу и обратно обойдется в " << round(cost*100)/100 << " руб." << std::endl;*/
	
	/*Напишите программу вычисления стоимости покупки с учетом скидки.Скидка в 3 % предоставляется, если сумма покупки больше 500 руб., в 5 % — если сумма покупки больше 1000 руб.*/

	/*double sum;
	std::cout << "Введите сумму покупки: ";
	std::cin >> sum;
	int disc = 0;
	if (sum >= 500 && sum <= 1000)
	{
		disc = 3;
	}
	else if (sum > 1000)
	{
		disc = 5;
	}
	std::cout.precision(2);
	std::cout << "Сумма с учетом скидки: " << std::fixed << round(calcDisc(sum, disc)*100)/100 << " руб.\n";*/

	/*Напишите программу, реализующую игру «Угадай число».*/

	std::array <int, 3> compMas{0};
	//int rdInt = getRdInt(0, 999);
	int rdInt = 8;
	getArr(compMas, rdInt);
	std::array <int, 3> userMas{ 0 };
	int userNumb;
	int countPlace;
	int countNumb;
	do
	{
		std::cout << "Ваш вариант: ";
		std::cin >> userNumb;
		getArr(userMas, userNumb);
		countPlace = 0;
		countNumb = 0;
		for (size_t i = 0; i < 3; i++)
		{
			if (userMas.at(i) == compMas.at(i))
			{
				++countPlace;
			}
			for (size_t j = 0; j < 3; j++)
			{				
				if (userMas.at(j) == compMas.at(i))
				{
					++countNumb;
					break;
				}
			}			
		}		
		std::cout << "Угадано: " << countNumb << ". На своих местах: " << countPlace << ".\n";
	} while (!(countPlace == 3 && countNumb == 3));
	std::cout << "***Вы угадали число " << rdInt << "!***\n";
	return 0;
}