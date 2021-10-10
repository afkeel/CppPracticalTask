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

	/*�������� ��������� ���������� ��������� ������� �� ���������� �� ����(���� � �������).*/

	/*double dist, rate_gas, exp_gas;
	double cost;
	std::cout << "���������� �� ���� (��): ";
	std::cin >> dist;
	std::cout << "������ ������� (������ �� 100 �� �������): ";
	std::cin >> exp_gas;
	std::cout << "���� ����� ������� (���.): ";
	std::cin >> rate_gas;
	cost = 2 * calcCost(dist, rate_gas, exp_gas);
	std::cout << "������� �� ���� � ������� ��������� � " << round(cost*100)/100 << " ���." << std::endl;*/
	
	/*�������� ��������� ���������� ��������� ������� � ������ ������.������ � 3 % ���������������, ���� ����� ������� ������ 500 ���., � 5 % � ���� ����� ������� ������ 1000 ���.*/

	/*double sum;
	std::cout << "������� ����� �������: ";
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
	std::cout << "����� � ������ ������: " << std::fixed << round(calcDisc(sum, disc)*100)/100 << " ���.\n";*/

	/*�������� ���������, ����������� ���� ������� �����.*/

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
		std::cout << "��� �������: ";
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
		std::cout << "�������: " << countNumb << ". �� ����� ������: " << countPlace << ".\n";
	} while (!(countPlace == 3 && countNumb == 3));
	std::cout << "***�� ������� ����� " << rdInt << "!***\n";
	return 0;
}