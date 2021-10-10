#include <iostream>
#include <array>
#include <random>
#include <cassert>
#include <time.h>
#include <functional>

using std::cout;
using std::cin;
constexpr auto ERROR_COUNT = 1000;
// получаем случайное число из диапазона от min до max
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	int range = max - min + 1;
	return static_cast<int>(rand() * fraction * range + min);
}
//проверяем полученные координаты на выход за размеры массива
bool checkArrayIndex(int x, int y, int row, int col)
{
	return x >= 0 && x < row&& y >= 0 && y < col;
}
//параметры карты
enum class MapParam
{
	LOSE,
	WIN,
	MISS,
	SHIP,
	SHIP_HIT,
	SHIP_SHOOT_DOWN,
	EMPTY_FIELD
};
// получаем символ соотвествующий параметру карты
char getIcon(MapParam m)
{
	switch (m)
	{
	case MapParam::MISS:
		return '+';
		break;
	case MapParam::SHIP:
		return '#';
		break;
	case MapParam::SHIP_HIT:
		return 'X';
		break;
	case MapParam::SHIP_SHOOT_DOWN:
		return 'X';
		break;
	case MapParam::EMPTY_FIELD:
		return '\xB7';
		break;
	default:
		return '0';
		break;
	}
}
// структура корабля
struct Ship
{
	char icon = getIcon(MapParam::EMPTY_FIELD);
	int id = 0;
};
//массив с кол-вом палуб корабля
struct ShipHP
{
	const size_t row = 20;
	const size_t col = 2;
	int arr[20 * 2]{};
	void check_index(int ship_hp_x, int ship_hp_y)
	{
		assert(checkArrayIndex(ship_hp_x, ship_hp_y, row, col));
	};
};
//вывод карты в консоль
void showMap(Ship* m, bool* mask, size_t row, size_t col, bool use_mask)
{
	cout << "  ";
	for (size_t i = 0; i < row; i++)
	{
		cout << i << " ";
	}
	cout << std::endl;
	for (size_t i = 0; i < row; i++)
	{
		cout << i << " ";
		for (size_t j = 0; j < col; j++)
		{
			if (mask[i * row + j] == 1 || use_mask == 0)
				cout << m[i * row + j].icon << " ";
			else cout << getIcon(MapParam::EMPTY_FIELD) << " ";
		}
		cout << "\n";
	}
	cout << std::endl;
}
//вывод результата хода в консоль
void showResult(MapParam res, int x, int y, bool player)
{
	player ? cout << "Координаты: (" << x << ", " << y << "). " :
		cout << "Координаты компьютера: (" << x << ", " << y << "). ";
	switch (res)
	{
	case MapParam::SHIP_HIT:
		cout << "Попал!\n";
		break;
	case MapParam::SHIP_SHOOT_DOWN:
		cout << "Убил!\n";
		break;
	case MapParam::MISS:
		cout << "Мимо!\n";
		break;
	default:
		break;
	}
}
//направление
enum class Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};
//сдвигаем координаты в зависимости от направления
void shiftCoord(int& x, int& y, Direction d)
{
	switch (d)
	{
	case Direction::UP: --x; break;
	case Direction::RIGHT: ++y; break;
	case Direction::DOWN: ++x; break;
	case Direction::LEFT: --y; break;
	default:
		break;
	}
}
//смена направления на противоположное
void reDir(Direction& dir)
{
	switch (dir)
	{
	case Direction::UP:
		dir = Direction::DOWN;
		break;
	case Direction::RIGHT:
		dir = Direction::LEFT;
		break;
	case Direction::DOWN:
		dir = Direction::UP;
		break;
	case Direction::LEFT:
		dir = Direction::RIGHT;
		break;
	default:
		break;
	}
}
// определяем направление по координатам
Direction defineDir(int t_x, int t_y, int x, int y)
{
	if (t_x == x && t_y < y) { return Direction::RIGHT; }
	else if (t_x == x && t_y > y) { return Direction::LEFT; }
	else if (t_y == y && t_x < x) { return Direction::DOWN; }
	else { return Direction::UP; }
}
//рисуем промахи вокруг потопленного корабля
void showShipSD(Ship* m, int x, int y, Direction dir, int map_size, int size_ship, bool* mask)
{
	int temp_x, temp_y;
	bool line_check = false;
	int count_line = size_ship + 2;
	reDir(dir);
	//сдвигаем на 1 клетку назад в зависимости от направления
	switch (dir)
	{
	case Direction::UP: ++x; line_check = true; break;
	case Direction::RIGHT: --y; break;
	case Direction::DOWN: --x; line_check = true; break;
	case Direction::LEFT: ++y; break;
	default:
		break;
	}
	for (int i = 0; i < count_line; i++)
	{
		int up_down = 0;
		int left_right = 0;
		//проверяем по три клетки начиная с крайней левой/нижней, двигаемся по 
		//горизонтали/вертикали(в зависимости от расположения корабля)
		//от отступа на 1 клетку до размер корабля + 2
		line_check ? up_down = -1 : left_right = -1;
		for (int i = 0; i < 3; i++)
		{
			temp_x = x + left_right;
			temp_y = y + up_down;
			if (checkArrayIndex(temp_x, temp_y, map_size, map_size))
			{
				if (m[temp_x * map_size + temp_y].icon == getIcon(MapParam::EMPTY_FIELD))
				{
					m[temp_x * map_size + temp_y].icon = getIcon(MapParam::MISS);
					mask[temp_x * map_size + temp_y] = 1;
				}
			}
			line_check ? ++up_down : ++left_right;
		}
		shiftCoord(x, y, dir);
	}
}
//проверяем возможность установки корабля
bool checkShip(Ship* m, int x, int y, Direction dir, int map_size, int size_ship)
{
	int temp_x, temp_y;
	temp_x = x;
	temp_y = y;
	for (int i = 0; i < size_ship; i++)
	{
		if (checkArrayIndex(temp_x, temp_y, map_size, map_size)) { shiftCoord(temp_x, temp_y, dir); }
		else { return 0; }
	}
	bool line_check = false;
	int count_line = size_ship + 2;
	//сдвигаем на 1 клетку назад в зависимости от направления
	switch (dir)
	{
	case Direction::UP: ++x; line_check = true; break;
	case Direction::RIGHT: --y; break;
	case Direction::DOWN: --x; line_check = true; break;
	case Direction::LEFT: ++y; break;
	default:
		break;
	}
	for (int i = 0; i < count_line; i++)
	{
		int up_down = 0;
		int left_right = 0;
		//проверяем по три клетки начиная с крайней левой/нижней, двигаемся по 
		//горизонтали/вертикали(в зависимости от расположения корабля)
		//от отступа на 1 клетку до размер корабля + 2
		line_check ? up_down = -1 : left_right = -1;
		for (int i = 0; i < 3; i++)
		{
			temp_x = x + left_right;
			temp_y = y + up_down;
			if (checkArrayIndex(temp_x, temp_y, map_size, map_size))
			{
				if (m[temp_x * map_size + temp_y].icon == getIcon(MapParam::SHIP))
				{
					return 0;
				}
			}
			line_check ? ++up_down : ++left_right;
		}
		shiftCoord(x, y, dir);
	}
	return 1;
}
// установка корабля
bool setShip(Ship* m, ShipHP& ship_hp, int x, int y, int map_size, int size_ship/*, bool* mask*/)
{
	bool ship_generate = false;
	static int ship_id = 0;
	int ship_hp_x = ship_id;
	int ship_hp_y = 0;
	Direction dir = static_cast<Direction>(getRandomNumber(0, 3));
	//если проверка прошла добавляем корабль в массив
	if (checkShip(m, x, y, dir, map_size, size_ship))
	{
		for (int i = 0; i < size_ship; i++)
		{
			m[x * map_size + y].icon = getIcon(MapParam::SHIP);
			m[x * map_size + y].id = ship_id;
			/*system("cls");
			showMap(m, mask, map_size, map_size, 0);
			getchar();*/
			shiftCoord(x, y, dir);
		}
		ship_generate = true;
		for (int i = 0; i < 2; i++)
		{
			ship_hp.check_index(ship_hp_x, ship_hp_y);
			ship_hp.arr[ship_hp_x * ship_hp.col + ship_hp_y] = size_ship;
			++ship_hp_y;
		}
		++ship_id;
	}
	return ship_generate;
}
//инициализация карты
void initMap(Ship* m, ShipHP& ship_hp, int map_size, int size_ship, int count_ship/*, bool* mask*/)
{
	int count = size_ship;
	for (int i = 0; i < count; i++)
	{
		int x, y;
		int try_set_ship = 0;
		//заполняем карту кораблями начиная с самого большого 
		//и уменьшая кол-во палуб до минимума
		//кол-во кораблей начинаем с 1 и увеличиваем  каждый раз на 1
		//после установки всех предыдущих
		for (int i = 0; i < count_ship; i++)
		{
			do
			{
				x = getRandomNumber(0, 9);
				y = getRandomNumber(0, 9);
				assert(checkArrayIndex(x, y, map_size, map_size));
				assert(++try_set_ship < ERROR_COUNT);
			} while (!setShip(m, ship_hp, x, y, map_size, size_ship/*, mask*/));
		}
		--size_ship;
		++count_ship;
	}
}
//ввод координад в консоли
void getCoordPlayer(int& x, int& y, int map_size)
{
	while (true)
	{
		cout << "Введите координаты через пробел (x y): ";
		cin >> x >> y;
		if (cin.fail() || !(checkArrayIndex(x, y, map_size, map_size)))
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Ошибка ввода.\n";
		}
		else
		{
			cin.ignore(32767, '\n');
			break;
		}
	}
}
//в зависимости от координат получаем результат хода
//попал, потопил, промазал
MapParam move(Ship* m, bool* mask, ShipHP& ship_hp, int map_size, int x, int y)
{
	MapParam result;
	int ship_hp_x = m[x * map_size + y].id;
	int ship_hp_y = 0;
	ship_hp.check_index(ship_hp_x, ship_hp_y);
	if (m[x * map_size + y].icon == getIcon(MapParam::SHIP))
	{
		if (ship_hp.arr[ship_hp_x * ship_hp.col + ship_hp_y] > 1)
		{
			m[x * map_size + y].icon = getIcon(MapParam::SHIP_HIT);
			result = MapParam::SHIP_HIT;
		}
		else
		{
			m[x * map_size + y].icon = getIcon(MapParam::SHIP_SHOOT_DOWN);
			result = MapParam::SHIP_SHOOT_DOWN;
		}
		--ship_hp.arr[ship_hp_x * ship_hp.col + ship_hp_y];
	}
	else
	{
		m[x * map_size + y].icon = getIcon(MapParam::MISS);
		result = MapParam::MISS;
	}
	mask[x * map_size + y] = 1;
	return result;
}
//делаем ход поочердно с компьютером
bool game(Ship* mc, Ship* mp, ShipHP& ship_hp, bool* mask_pl, bool* mask_cp, int map_size, int ships)
{
	bool player_move = true;
	static int total_pl_ship = ships;
	static int total_cp_ship = ships;
	MapParam move_result;
	Direction cp_dir = Direction::UP;
	int x_bot, y_bot, firstHitX, firstHitY;
	int mode = 0;
	int try_get_coord = 0;
	int prev_x = 0;
	int prev_y = 0;
	bool hit_mode = true;
	//играем пока кол-во кораблей соперника не будет равно нулю
	while (total_pl_ship && total_cp_ship)
	{
		do
		{
			//делаем ход пока не промажем
			if (player_move)
			{
				int x, y;
				getCoordPlayer(x, y, map_size);
				assert(checkArrayIndex(x, y, map_size, map_size));
				move_result = move(mc, mask_cp, ship_hp, map_size, x, y);
				if (move_result == MapParam::SHIP_HIT)
				{
					prev_x = x;
					prev_y = y;
				}
				else if (move_result == MapParam::SHIP_SHOOT_DOWN)
				{
					int ship_hp_x = mc[x * map_size + y].id;
					int ship_hp_y = 1;
					ship_hp.check_index(ship_hp_x, ship_hp_y);
					int size_ship = ship_hp.arr[ship_hp_x * ship_hp.col + ship_hp_y];
					--total_cp_ship;
					Direction pl_dir = defineDir(prev_x, prev_y, x, y);
					showShipSD(mc, x, y, pl_dir, map_size, size_ship, mask_cp);
				}
				system("cls");
				showMap(mp, mask_pl, map_size, map_size, 0);
				showMap(mc, mask_cp, map_size, map_size, 1);
				showResult(move_result, x, y, player_move);
			}
			else
			{
				switch (mode)
				{
				case 0:
					do
					{
						x_bot = getRandomNumber(0, 9);
						y_bot = getRandomNumber(0, 9);
						assert(++try_get_coord < ERROR_COUNT);
					} while (mask_pl[x_bot * map_size + y_bot] == 1);
					assert(checkArrayIndex(x_bot, y_bot, map_size, map_size));
					move_result = move(mp, mask_pl, ship_hp, map_size, x_bot, y_bot);
					showResult(move_result, x_bot, y_bot, player_move);
					break;
				case 1:
					while (true)
					{
						if (hit_mode) { cp_dir = static_cast<Direction>(getRandomNumber(0, 3)); }
						shiftCoord(x_bot, y_bot, cp_dir);
						if (checkArrayIndex(x_bot, y_bot, map_size, map_size) &&
							!(mask_pl[x_bot * map_size + y_bot] == 1))
						{
							assert(checkArrayIndex(x_bot, y_bot, map_size, map_size));
							move_result = move(mp, mask_pl, ship_hp, map_size, x_bot, y_bot);
							showResult(move_result, x_bot, y_bot, player_move);
							break;
						}
						else
						{
							x_bot = firstHitX;
							y_bot = firstHitY;
							if (!hit_mode) { reDir(cp_dir); }
						}
						assert(++try_get_coord < ERROR_COUNT);
					}
					break;
				default:
					break;
				}
				/*getchar();
				system("cls");
				showMap(mp, mask_pl, map_size, map_size, 0);
				showMap(mc, mask_cp, map_size, map_size, 1);*/
				if (mode == 0)
				{
					if (move_result == MapParam::SHIP_HIT)
					{
						mode = 1;
						firstHitX = x_bot;
						firstHitY = y_bot;
					}
				}
				else if (mode == 1)
				{
					if (move_result == MapParam::MISS)
					{
						x_bot = firstHitX;
						y_bot = firstHitY;
						if (!hit_mode) { reDir(cp_dir); }
					}
					else if (move_result == MapParam::SHIP_HIT) { hit_mode = false; }
				}
				if (move_result == MapParam::SHIP_SHOOT_DOWN)
				{
					int ship_hp_x = mp[x_bot * map_size + y_bot].id;
					int ship_hp_y = 1;
					ship_hp.check_index(ship_hp_x, ship_hp_y);
					int size_ship = ship_hp.arr[ship_hp_x * ship_hp.col + ship_hp_y];
					showShipSD(mp, x_bot, y_bot, cp_dir, map_size, size_ship, mask_pl);
					--total_pl_ship;
					mode = 0;
					hit_mode = true;
				}
			}
		} while (move_result != MapParam::MISS && total_pl_ship && total_cp_ship);
		player_move = !player_move;
	}
	return total_cp_ship ? static_cast<int>(MapParam::LOSE) : static_cast<int>(MapParam::WIN);
}

int main()
{
	/*srand(static_cast<unsigned int>(time(0)));
	rand();*/
	setlocale(0, "");
	//объявляем и инициализируем переменные
	const size_t map_size = 10;
	const size_t ships = 10;
	int size_ship = 4;
	int count_ship = 1;
	Ship map_player[map_size * map_size]{};
	Ship map_comp[map_size * map_size]{};
	bool map_mask_pl[map_size * map_size]{};
	bool map_mask_cp[map_size * map_size]{};
	ShipHP ship_hp;
	//заполняем и рисуем карты
	initMap(map_player, ship_hp, map_size, size_ship, count_ship/*, mask_pl_ptr*/);
	initMap(map_comp, ship_hp, map_size, size_ship, count_ship/*, mask_cp_ptr*/);
	showMap(map_player, map_mask_pl, map_size, map_size, 0);
	showMap(map_comp, map_mask_cp, map_size, map_size, 1);
	//играем
	bool end_game = game(map_comp, map_player, ship_hp, map_mask_pl, map_mask_cp, map_size, ships);
	//выводим результат
	system("pause");
	system("cls");
	showMap(map_player, map_mask_pl, map_size, map_size, 0);
	showMap(map_comp, map_mask_cp, map_size, map_size, 1);
	if (end_game)
		cout << "Вы победили!\n";
	else
		cout << "Вы проиграли!\n";
	return 0;
}