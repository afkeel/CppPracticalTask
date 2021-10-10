#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

bool isIcecreamSandwich(const std::string& str)
{
	bool ret = false;
	size_t l = str.length();
	size_t mid = l / 2;

	//условие дл€ "AA"
	if (str.length() >= 3)
	{
		//условие дл€ "BBBBBBBBBB"
		if (str[mid] != str[0] || str[mid] != str[l - 1])
		{
			//условие дл€ "AAACCCAA"
			for (size_t i = 0, j = l - 1; i < mid; i++, j--)
			{
				if (str[i] != str[j])
				{
					return ret;
				}
			}
			//условие дл€ "AACDCAA"
			for (size_t i = 0; i <= mid; i++)
			{
				if (str[i] != str[0] && str[i] != str[mid])
				{
					return ret;
				}
			}
			ret = true;
		}
	}
	return ret;
}

//bool isIcecreamSandwich(const std::string& checkString)
//{
//	if (checkString.size() < 3) return false;
//	int tempCount = 0;
//	for (int i = 1; i < checkString.size(); i++)
//	{
//		if (checkString[i - 1] != checkString[checkString.size() - i]) return false;
//		if (checkString[i - 1] != checkString[i]) tempCount++;
//	}
//	if (tempCount != 2) return false;
//	return true;
//}

int myFind(const std::vector <int>& mas)
{
	size_t l = mas.size();
	int min = mas.at(0);

	for (size_t i = 1; i < l; i++)
	{
		if (min > mas.at(i))
		{
			min = mas.at(i);
		}
	}
	return min;
}

//template<class ForwardIt>
//ForwardIt min_element(ForwardIt first, ForwardIt last)
//{
//	if (first == last) return last;
//
//	ForwardIt smallest = first;
//	++first;
//	for (; first != last; ++first) {
//		if (*first < *smallest) {
//			smallest = first;
//		}
//	}
//	return smallest;
//}

int getValue()
{
	int n;
	do
	{
		std::cout << "Enter number month: ";
		std::cin >> n;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
		{
			std::cin.ignore(32767, '\n');
			if (std::cin.gcount() > 1) //если очистили более 1 символа, т.е. был мусор
			{
				n = 0;
			}
		}
	} while (n < 1 || n > 12);

	return n;
}

int main()
{
	/*Ќапишите программу, котора€ запрашивает у пользовател€ номер мес€ца и затем выводит соответствующее название времени года.¬ случае, если пользователь введет недопустимое число, программа должна вывести сообщение об ошибке.*/
	
	int numb_m  = getValue();	
	switch (numb_m)
	{
	case 12:
	case 1:
	case 2:
	{
		std::cout << "Winter\n";
		break;
	}
	case 3:
	case 4:
	case 5:
	{
		std::cout << "Spring\n";
		break;
	}
	case 6:
	case 7:
	case 8:
	{
		std::cout << "Summer\n";
		break;
	}
	case 9:
	case 10:
	case 11:
	{
		std::cout << "Autumn\n";
		break;
	}
	default:
		break;
	}

	/*Ќапишите программу, котора€ возвращает true, если строка, введенна€ пользователем, €вл€етс€ сэндвичем с мороженым, и false Ч в противном случае.*/
	
	/*std::cout << std::boolalpha;
	std::cout << isIcecreamSandwich("ABABA") << std::endl;*/

	/*Ќапишите программу, котора€ определ€ет минимальное число в последовательности положительных чисел, которую ввел пользователь.≈сли в последовательности есть отрицательные числа, то вы должны сообщить об этом пользователю и предложить повторить ввод еще раз.*/

	/*int numb = 0;
	std::vector <int> mas;

	std::cout << "Enter numbers: ";
	do
	{
		std::cin >> numb;
		if (numb >= 0)
		{
			mas.push_back(numb);
		}
		else
		{
			std::cout << "Number is negative!\n";
			std::cin.ignore(32767, '\n');
			std::cout << "Enter numbers: ";
		}
	} while (std::cin.peek() != '\n');
	std::cin.ignore(32767, '\n');
	
	std::cout << "Min element: " << myFind(mas) << std::endl;*/
	//std::cout << "Min element: " << *(std::min_element(mas.begin(), mas.end())) << std::endl;

	/*int min_element = INT32_MAX;
	int numb = 0;	
	std::cout << "Enter numbers: ";
	do
	{		
		std::cin >> numb;
		if (numb >= 0)
		{
			min_element = numb > min_element ? min_element : numb;
		}
		else
		{
			std::cout << "Number is negative!\n";
			std::cin.ignore(32767, '\n');
			std::cout << "Enter numbers: ";
		}
	} while (std::cin.peek() != '\n');
	std::cout << "Min element: " << min_element << std::endl;*/

	return 0;
}