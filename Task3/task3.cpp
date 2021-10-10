#include <iostream>
#include "myfh.h"
#include <map>
#include <fstream>
#include <windows.h>

double spd(double l, double t)
{
	double intpart;
	double fractpart = modf(t, &intpart)*100.;
	t = (intpart * minute + fractpart) / hour;
	l /= kilometer;
	return l / t;
}

template <typename T>
T get_valaue(const char* s)
{
	T x;
	bool ret{};
	do
	{
		ret = false;
		x = enter_val<T>(s);
		if (x <= 0)
		{
			std::cout << "�������� ������ ��� ����� ����!\n";
			ret = true;
		}
	} while (ret);
	return x;
}

int seq_even_sum(int x)
{
	int sum = 0;
	for (int i = 1; i <= x; i++)
	{
		sum += i * 2;
	}
	return sum;
}

using Map = std::map<char, std::string >;
void show_map(const Map& m)
{
	int z{};
	for (const auto& pair : m)
	{
		std::cout << pair.first << pair.second << "\t";
		++z;
		if (z % 4 == 0) { std::cout << "\n"; }
	}
}

bool find_symbol(char ch, std::string& s, const Map& m)
{
	if (ch == '�') ch = '�';
	auto found{ m.find(ch) };
	if (found != m.end())
	{
		s = found->second;
	}
	return found != m.end();
}

void beeper(const std::string& s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '�')
			Beep(1500, 200);
		if (s[i] == '-')
			Beep(1500, 500);
	}
}

int main()
{	
	/*�������� ��������� - ��������, ������� ��������� �� ������������ ��������� � ������� ��� �� ����� � ���� ������������������ ����� � ����.����� ����� � ���� ����� ������������ �������� �������� ��������������� ������������.*/

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Map morse_code;
	std::ifstream inf;
	inf.open("morse_code.txt");
	if (!inf)
	{
		exit(1);
	}
	while (inf)
	{
		char map_first;
		inf >> map_first;
		std::string map_second;
		inf >> map_second;
		morse_code.emplace(std::make_pair(map_first, std::move(map_second)));
	}
	show_map(morse_code);
	char symbol{};
	std::string msg;
	std::cout << "������� ���������: \n";
	setlocale(0, ""); // ��� toupper
	do
	{
		std::cin >> symbol;
		if (find_symbol(toupper(symbol), msg, morse_code))
		{
			std::cout << msg;
			beeper(msg);
		}
		else
		{
			std::cout << "������ � ���������!\n";
			std::cin.ignore(32767, '\n');
			std::cout << "������� ���������: \n";
		}

	} while (std::cin.peek() != '\n');
	std::cout << std::endl;

	/*�������� ���������, ������� ��������� ����� ������ n ����� ������������� ������ �����.���������� ����������� ����� ������ ������������.*/

	/*int num = get_valaue<int>("������� ���������� ����������� �����: ");
	std::cout << "����� ������ " << num << " ����� ������������� ������ ����� ����� " << seq_even_sum(num) << std::endl;*/

	/*�������� ���������, ����������� ��������, � ������� ����� �������� ���������.*/

	/*double len = get_valaue<double>("������� ����� ��������� (�): ");
	double t = get_valaue<double>("������� ����� (�����.������): ");
	std::cout.precision(4);
	std::cout << "�� ������ �� ��������� " << spd(len, t) <<" ��/���.\n";*/

	return 0;
}