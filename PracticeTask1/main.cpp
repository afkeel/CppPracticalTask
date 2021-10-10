#include <iostream>
#include <fstream>

/*Найти все натуральные числа, меньшие N, в записи которых имеется K подряд идущих нулей. Ответ записать в файл
с именем d.dat, располагая по одному числу в строке. Если таких чисел нет, то результирующий файл должен быть
создан, но пуст.*/

int main()
{
	int natural_numb, k;
	do
	{
		std::cout << "Enter N, K: ";
		std::cin >> natural_numb >> k;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
	} while (natural_numb <= 0 || k <= 0);
	std::cin.ignore(32767, '\n');

	std::ofstream outf("d.dat");
	if (!outf)
	{
		std::cout << "Error!";
		return -1;
	}
	int j = 1;
	int count_zero = 0;
	int count_seq = 0;
	int prev = -1;
	for (int i = 1; i < natural_numb; i++)
	{
		int x = i;
		while (x != 0)
		{
			int digit = x % 10;
			x /= 10;
			if (digit == 0)
			{
				++count_zero;
				if (digit == prev)
				{
					++count_seq;
				}
			}
			prev = digit;
		}
		if (count_zero >= k && count_seq >= k - 1)
		{
			outf << j << ": \"" << i << "\"\n";
			++j;
		}
		count_zero = 0;
		count_seq = 0;
		prev = -1;
	}

	return 0;
}