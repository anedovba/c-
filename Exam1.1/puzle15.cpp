#include "puzle15.h"

using namespace std;
puzle15::puzle15()
{
	
	
	ints = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	// Random seed generator
	random_device rd;
	// Psuedo random number generator
	mt19937 prng(rd());
	// Shuffle the 0,1,2,3..., integer sequence
	shuffle(ints.begin(), ints.end(), prng);
	intsCopy = ints;

	mass_a = { -1, -1, -1, -1 };
	trassa = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	open_list = { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } };
	Min_F=100;
	count_step=0;

}


puzle15::~puzle15()
{
}
void puzle15::NewFile(){
	
		
	char pass[100] = "1.txt";
	FILE *pf;
	fopen_s(&pf, pass, "r");

	struct str
	{
		char S[4];
	};
	int count = 0;
	char s[4];
	while (!feof(pf))//считаем количество строк
		{
			count++;
			fgets(s, 4, pf);
		}
		rewind(pf);//переносим курсор на начало файла
		str*MAS = new str[count];//создаем массив рамером посчитанных строк
		for (int i = 0; i < count; i++)//заполняем массив строками с файла
		{
			fgets(MAS[i].S, 4, pf);
		}
		for (int i = 0; i < 16; i++){
			ints[i] = atoi(MAS[i].S);
		}
			
	fclose(pf);
	intsCopy = ints;
}

void puzle15::Print(){
	
	for (int i = 0; i < 16; i++){
		cout << ints[i] << "\t";
		if ((i + 1) % 4 == 0) cout << endl << endl;
	}
	
	cout << endl;
}
void puzle15::PrintCopy(){

	for (int i = 0; i < 16; i++){
		cout << intsCopy[i] << "\t";
		if ((i + 1) % 4 == 0) cout << endl << endl;
	}

	cout << endl;
}
bool puzle15::Check(){//проверка на возможность решения головоломки
	int inv = 0;
	for (int i = 0; i<16; ++i)
		if (ints[i])
			for (int j = 0; j<i; ++j)
				if (ints[j] > ints[i])
					++inv;
	for (int i = 0; i<16; ++i)
		if (ints[i] == 0)
			inv += 1 + i / 4;
	if (inv & 1) {
		cout << "\n--------Unable to solve!!! Try again.------------\n";
		return true;//решение отсутствует
	}
}
int puzle15::Epmty()
{
	for (int i = 0; i<16; i++)
		if (intsCopy[i] == 0)
			return i;
}

void puzle15::Move(char c)//передвижение пустого поля
{
	int x = Epmty();
	switch (c)
	{
	case '4':
	{
		if ((x != 0) && (x != 4) && (x != 8) && (x != 12))
		{
			swap(intsCopy[x], intsCopy[x - 1]);
		}
	} break;
	case '8':
	{
		if ((x != 0) && (x != 1) && (x != 2) && (x != 3))
		{
			swap(intsCopy[x], intsCopy[x - 4]);
		}
	} break;
	case '6':
	{
		if ((x != 3) && (x != 7) && (x != 11) && (x != 15))
		{
			swap(intsCopy[x], intsCopy[x + 1]);
		}
	} break;
	case '2':
	{
		if ((x != 12) && (x != 13) && (x != 14) && (x != 15))
		{
			swap(intsCopy[x], intsCopy[x + 4]);
		}
	} break;
	}
}
void puzle15::Moving(char c){
	switch (c) //В зависимости от нажатой клавиши (от ее целочисленного кода) двигаем костяшки
	{
	case '4': Move('4'); break; //Нажата клавиша "Влево"
	case '8': Move('8'); break; //Нажата клавиша "Вверх"
	case '6': Move('6'); break; //Нажата клавиша "Вправо"
	case '2': Move('2'); break; //Нажата клавиша "Вниз"
	case '0': exit(0); //Нажата клавиша "Escape"
	}
}
bool puzle15::FieldIsCorrect()
{
	for (int i = 0; i < 15; i++)
		if (intsCopy[i] != i + 1)
			return false; //При первом же нахождении несоответствия выходим и возвращаем false
	return true;//Если не найдено ни одного несоответствия - поле собрано верно
}

void puzle15::Trasser_Init(void) //инициализация массивов для трассера
{
	close_list.clear();
	for (int i = 0; i < 16; i++)//инициализация массивов (-1)
	{

		if (!map.empty())//если в массиве собр элементов уже есть элемент то переносим его в в закрытый лист
			close_list.insert(close_list.end(), map.begin(), map.end());//переносим элемент из массива сборки в массив закрытых при трассировке элементов

		if (!n_block.empty())//если в массиве блокировок уже есть элемент то переносим его в закрытый лист
			close_list.insert(close_list.end(), n_block.begin(), n_block.end());//переносим элемент из массива блокировки в массив закрытых при трассировке элементов

		trassa[i] = -1;//массив точек маршрута
		//обнуляем массив открытый список точек
		open_list[i].F = 0;
		open_list[i].G = 0;
		open_list[i].H = 0;
		open_list[i].Poz = 0;
	}
	Min_F = 100;
}
int puzle15::FindElements(int n) //функция поиск позиции числа
{
	for (int i = 0; i<16; i++)
		if (ints[i] == n)
			return i;
}

int puzle15::Steps(int a, int b)//подсчет числа шагов к от одной точки к другой
{
	int step = 0, tmp;
	if (b<a)
	{
		swap(a, b);
	}
	while (a != b)
	{
		if (b>a&&a / 4 != b / 4) //если b больше а и они в разных строках
		{
			a = a + 4;//переходим на другую строку
			step++;//делаем шаг
		}
		if (b>a&&a / 4 == b / 4) //если b больше a и они в одной строке
		{
			a++;//переходим на другую ячейку
			step++;//делаем шаг
		}
		if (b<a)
		{
			a--;
			step++;
		}
	}
	return step;
}

bool puzle15::Check_Block_Position(int p)//проверка заблокирована ли данная позиция в массиве блокированных элементов n_block
{
	if (find(close_list.begin(), close_list.end(), p) != close_list.end())//проверяем значение в закрытом списке (если заблокирован то элемент массива содержит этот индекс=р)
		return true;//блокирован
	else
		return false;//не блокирован
}

int puzle15::Trasser_Area(static int aa)
{
	int d = 0;//кол-во направлений из этой точки
	int _r;
	if ((aa - 1) / 4 == (aa / 4))//есть ли рядом слева элемент на той же строке
	{
		if (!Check_Block_Position(aa - 1))//если элемент слева не блокирован
			mass_a[0] = aa - 1; //записываем он не блокирован
		else
			mass_a[0] = -1; //не записываем, он блокирован
	}
	else
		mass_a[0] = -1;//елемента слева нет он за левой границей 

	if ((aa + 1) <= 15 && (aa + 1) / 4 == aa / 4)//есть ли рядом справа элемент на той же строке
	{
		if (!Check_Block_Position(aa + 1))//если элемент справа не блокирован
			mass_a[1] = aa + 1; //записываем он не блокирован
		else
			mass_a[1] = -1;	//не записываем, он блокирован	
	}
	else
		mass_a[1] = -1;//елемента справа нет он за правой границей 

	if ((aa - 4) >= 0)//есть ли над этим элементом элемент выше
	{
		if (!Check_Block_Position(aa - 4))//если элемент сверху не блокирован
			mass_a[2] = aa - 4;//записываем он не блокирован
		else
			mass_a[2] = -1;	//не записываем, он блокирован	
	}
	else
		mass_a[2] = -1;//елемента сверху нет он за верхней границей 

	if ((aa + 4) <= 15)//есть ли над этим элементом элемент ниже
	{
		if (!Check_Block_Position(aa + 4))//если элемент снизу не блокирован
			mass_a[3] = aa + 4;//записываем он не блокирован
		else
			mass_a[3] = -1;	//не записываем, он блокирован	
	}
	else
		mass_a[3] = -1;//елемента снизу нет он за нижней границей 

	for (_r = 0; _r<4; _r++)//подсчет числа направлений
	{
		if (mass_a[_r] != -1)
			d++;
	}

	return d;
}

int puzle15::Trass_Parent(int parent) //функция установки новой точки родителя 
{
	int i, el;

	for (i = 0; i<4; i++)
	{
		el = mass_a[i];
		if (el != -1)
		{
			if (Min_F >= open_list[el].F)
			{
				if (open_list[el].Direct != 0)//исключаем напрвления с тупиками
				{
					Min_F = open_list[el].F;
					parent = open_list[el].Poz;
				}
			}
		}
	}
	return parent;
}

void puzle15::Trasser_patch(int start, int finish)//создаем машрут из точки А в точку В (алгоритм А*)
{
	int rod = start; //начальный родитель - стартовая точка
	int old_rod = start;//предыдущий родитель - стартовая точка
	int count_rod = 0;
	int i;
	int direct = 0; //количесво разрешенных направлений из данной точки
	int count_point = 0;//счетчик точек маршрута
	int n_step; //кол-во перемещений в данную точку из стартовой

	open_list[start].Poz = start; //позиция элемента
	open_list[start].G = 0;//G = стоимость передвижения из стартовой точки A к данной клетке, следуя найденному пути к этой клетке.
	//(будем считать что стоимость передвижения на 1 позицию =10)
	open_list[start].H = Steps(start, finish) * 10;/*H = примерная стоимость передвижения от данной клетки до целевой, то есть точки B.
												   Она обычно является эвристической функцией.*/
	//Стоимость H посчитана с помощью вычисления Манхеттенского расстояния к точке В, 
	//двигаясь только по горизонтали и вертикали, игнорируя все препятствия на пути.
	open_list[start].F = open_list[start].G + open_list[start].H; //Стоимость F для каждой клетки вычисляется простым суммированием G и H.
	//open_list[start].Dst = abs(finish-start); //разность между начальной точкой и конечной

	if (!n_block.empty())//добавление в закрытый список элементов из списка блокировки 
	{
		close_list.insert(close_list.end(), n_block.begin(), n_block.end());//добавляем его в закрытый список
	}

	open_list[finish].Poz = finish;//добавим в открытый список конечную точку
	open_list[finish].H = -1;//инициализация финишной точки, чтобы мы могли войти в цикл

	while (open_list[finish].H != 0) //строим маршрут пока не достигли конечной точки т.е при H=0 мы находимся в кон. точке
	{
		//count_step++;
		direct = Trasser_Area(rod);//формируем масив mass_a окружения родительской точки и определяем число направлений из родительской точки
		close_list.push_back(rod); //заносим стартовую точку в закрытый список

		for (i = 0; i<4; i++)//заполняем open_list исходя из массива окружения родителя
		{
			n_step = 10;//инициализация стомости перехода на 1 шаг
			int ar = mass_a[i];//сохраняем элемент окружения в open_list (в этом массиве [0] -точка справа [1]-точка слева [2]-точка сверху [3]-точка снизу)
			if (ar != -1)//если элемент = -1 то соседней точки с какой либо стороны нет либо она заблокирована в close_list
			{
				open_list[ar].Poz = ar; //позиция элемента

				for (int c = 0; c<16; c++) //сканируем уже созданную часть маршрута и считаем сколько ячеек мы уже прошли
				{
					if (trassa[c] != -1)
						n_step += 10;//определим стоимость передвижения из одной ячейки =10 и будем ее накапливать
				}
				open_list[ar].G = n_step; //заносим стоимость перемещения из стартовой в эту ячейку
				open_list[ar].H = ((Steps(ar, finish)) * 10);//заносим стоимость перемещения из данной ячейки в конечную
				open_list[ar].F = open_list[ar].G + open_list[ar].H;//вычисляем F=G+H;
				open_list[ar].Direct = direct;//записываем кол-во разрешенных направлений из родительской точки;
			}
		}
		old_rod = rod;
		rod = Trass_Parent(rod);//получаем родителя 

		if (count_point<16 && old_rod != rod)//если счетчик циклов не превышает размер массива маршрута и старый и новый родители не совпадают
		{
			trassa[count_point] = rod;//записываем точку маршрута в массив
			count_point++;//увеличиваем счетчик точек маршрута
			Min_F = 100;
		}
		if (old_rod == rod)//если старый и новый родители совпадают будем их подсчитывать
			count_rod++;
		if (count_rod == 10)
		{
			break;
		}

		if (count_point >= 16)//блок контроля ошибок
		{
			cout << "Переполнение trassa Блок Trasser" << endl;
			break;
		}
	}//End while
}

void puzle15::SwapElements(int num) //функция обмен местами элементов если пустая ячейка рядом
{
	int zero;
	for (int i = 0; i<16; i++)
	{
		if (ints[i] == 0){
			zero = i;
			break;
		}
	}
	int Num = ints[num];
	if (num == zero + 1 || num == zero - 1 || num == zero - 4 || num == zero + 4)//если рядом с элементом по адресу num находится пробел 
	{
		ints[zero] = Num;//записываем значение элемента в ячейку где был 0
		ints[num] = 0;	//записываем 0 в ячейку где был элемент
		count_step++;
		system("cls");
		cout << "\tNext step\n\n";
		Print();
		system("pause");

	}
}

void puzle15::ZeroPositions(int n) //функция сдвинуть пустую ячейку в любую нужную позицию
{
	int p_zero = FindElements(0);//находим адрес "0" в таблице
	int i;
	if (p_zero == n)//если ноль уже в нужной позиции то возврат
		return;

	Trasser_patch(p_zero, n);//создаем маршрут от положения 0(p_zero) к указанной точке(n)

	for (i = 0; i<16; i++)//перебор точек маршрута
	{
		if (trassa[i] != -1)//если есть точка (число не равное -1)

		{
			SwapElements(trassa[i]);//меняем 0 с элементом маршрута
		}
	}
	Trasser_Init();

}

void puzle15::Set_ElementPosition(int number, int ni) //Поставить число в нужную позицию
{
	int poz_number = FindElements(number);
	int n_column = ni % 4;//вычисляем номер колонки для позиции
	int n_line = ni / 4;//вычисляем номер строки для позиции
	int el_column;//номер колонки для элемента
	int el_line;//номер строки для элемента

	if (ni == poz_number)//если элемент на месте то возврат
		return;

	while (ni != poz_number)//выполняем пока не достигли нужной позиции
	{
		el_column = poz_number % 4;//вычисляем номер колонки для элемента
		el_line = poz_number / 4;//вычисляем номер строки для элемента

		n_block.push_back(poz_number);//блокируем эту точку перед позиционированием пробела
		if (el_column<n_column)//если позиция элемента слева от нужной колонки
		{

			ZeroPositions(int(poz_number + 1));//устанавливаем пустую клетку справа
			SwapElements(poz_number); //меняем местами с пустой клеткой
			//n_block.erase(find(n_block.begin(), n_block.end(), poz_number));//снимаем блокировку точки после позиционирования пробела
		}

		if (el_column>n_column)//если позиция элемента справа от нужной колонки
		{
			//n_block.push_back(poz_number);//блокируем эту точку перед позиционированием пробела
			ZeroPositions(int(poz_number - 1));//устанавливаем пустую клетку слева 
			SwapElements(poz_number); //меняем местами с пустой клеткой 
			//n_block.erase(find(n_block.begin(), n_block.end(), poz_number));//снимаем блокировку точки после позиционирования пробела

		}

		if ((el_column == n_column) && (el_line>n_line))//если элемент находится в колонке но его позиция ниже нужной строки
		{
			//n_block.push_back(poz_number);//блокируем эту точку перед позиционированием пробела
			ZeroPositions(int(poz_number - 4));//устанавливаем пустую клетку сверху
			SwapElements(poz_number); //меняем местами с пустой клеткой
			//n_block.erase(find(n_block.begin(), n_block.end(), poz_number));//снимаем блокировку точки после позиционирования пробела
		}
		if ((el_column == n_column) && (el_line<n_line))//если элемент находится в колонке но его позиция выше нужной строки
		{
			//n_block.push_back(poz_number);//блокируем эту точку перед позиционированием пробела
			ZeroPositions(int(poz_number + 4));//устанавливаем пустую клетку снизу
			SwapElements(poz_number); //меняем местами с пустой клеткой

		}
		n_block.erase(find(n_block.begin(), n_block.end(), poz_number));//снимаем блокировку точки после позиционирования пробела
		Trasser_Init();//инициализация массивов трассировки
		poz_number = FindElements(number);

	}
}

int puzle15::Make_Line_1(void)
{
	Trasser_Init();//инициализация массивов
	if (ints[0] == 1 && ints[1] == 2 && ints[2] == 3 && ints[3] == 4)//если 1,2,3,4 на свойх местах то нам повезло
	{
		map.push_back(0);
		map.push_back(1);
		map.push_back(2);
		map.push_back(3);
		//блокируем весь ряд он сложен
		return count_step; //возвращаемся нам повезло!!!!
	}
	//сборка 1-го ряда **************************************************************************************

	Set_ElementPosition(1, 0);
	if (ints[0] == 1)
		map.push_back(0); //блокируем ячейку 0 (с цифрой 1)
	Trasser_Init();
	Set_ElementPosition(2, 1);
	if (ints[1] == 2)
		map.push_back(1); //блокируем ячейку 1 (с цифрой 2)
	Trasser_Init();
	if (ints[0] == 1 && ints[1] == 2)//Если первая и вторaя ячейка на месте
	{

		while (true){
			Trasser_Init();
			Set_ElementPosition(4, 11);


			Set_ElementPosition(3, 3);
			if (ints[3] == 3)//Если ячейка 3 на месте
				map.push_back(3); //блокируем ячейку 3 (с цифрой 3)
			Trasser_Init();

			Set_ElementPosition(4, 7);//ставим 4 в ячейку 7
			if (ints[7] == 4)
				map.push_back(7); //блокируем ячейку 7 (с цифрой 4)
			Trasser_Init();

			if ((ints[3] == 3) && (ints[7] == 4))
			{
				ZeroPositions(2);//ставим пустую ячейку на ячейку 2
				map.erase(find(map.begin(), map.end(), 3)); //снимаем блокировку с ячейки 3 (с цифрой 3)
				map.erase(find(map.begin(), map.end(), 7)); //снимаем блокировку с ячейки 7 (с цифрой 4)
				Trasser_Init();
				SwapElements(3);//ставим 3 в ячейку 2

				SwapElements(7);//ставим 4 в ячейку 3

				if ((ints[2] == 3) && (ints[3] == 4))//если 3 и 4 в своих ячейках
				{
					map.push_back(2); //блокируем ячейку 2 (с цифрой 3)
					map.push_back(3); //блокируем ячейку 3 (с цифрой 4)
					Trasser_Init();
					break;
				}
				else
				{
					map.erase(find(map.begin(), map.end(), 2)); //разблокируем ячейку 2 (с цифрой 3)
					map.erase(find(map.begin(), map.end(), 3)); //разблокируем ячейку 3 (с цифрой 4)
					Trasser_Init();
				}
			}
		}
	}
	Trasser_Init();
	return count_step;
}
int puzle15::Make_Line_2(void)
{
	if (ints[4] == 5 && ints[5] == 6 && ints[6] == 7 && ints[7] == 8)//если элементы 5,6,7,8 на свойх местах
	{
		map.push_back(4);
		map.push_back(5);
		map.push_back(6);
		map.push_back(7); //блокируем весь ряд, он сложен
		return count_step; //возвращаемся нам повезло!!!!
	}
	Trasser_Init();//инициализация массивов
	//сборка 2-го ряда *******************************************************
	// 
	while (true)//выполняем пока элементы 5,6,7,8 не будут на свойх местах
	{
		Set_ElementPosition(5, 4);
		if (ints[4] == 5)
			map.push_back(4); //блокируем ячейку 4 (с цифрой 5)
		Trasser_Init();
		Set_ElementPosition(6, 5);
		if (ints[5] == 6)
			map.push_back(5);//блокируем ячейку 5 (с цифрой 6)
		Trasser_Init();
		if (ints[4] == 5 && ints[5] == 6)//Если цифра 5 и 6 на месте то далее
		{
			while (ints[7] != 7)
			{
				Set_ElementPosition(7, 7);//переход на позиционирование 7
				if (ints[7] == 7)
					map.push_back(7);//блокируем ячейку 7 (с цифрой 7)
				Trasser_Init();
				if (ints[6] == 8)//Если цифра 8 случайно была установлена на позицию 6 тогда сдвигаем ее в поз 8, если этого не сделать, то она заблокируется в ряду и ее невозможно будет вынуть
				{
					//map.erase(find(map.begin(), map.end(), 6));
					map.erase(find(map.begin(), map.end(), 7));
					Trasser_Init();
					Set_ElementPosition(8, 14);
					Set_ElementPosition(7, 7);
					map.push_back(7);//блокируем ячейку 7 (с цифрой 7)
				}
			}

			Set_ElementPosition(8, 11);//ставим 8 в ячейку 11
			if (ints[11] == 8)
				map.push_back(11);//блокируем ячейку 11 (с цифрой 8)
			Trasser_Init();
			ZeroPositions(6);//ставим пустую ячейку на ячейку 6 //потом будем менять местами соседние ячейки
			if (find(map.begin(), map.end(), 7) != map.end())
				map.erase(find(map.begin(), map.end(), 7)); //снимаем блокировку с ячейки 7 (с цифрой 7)
			map.erase(find(map.begin(), map.end(), 11)); //снимаем блокировку с ячейки 11 (с цифрой 8)
			Trasser_Init();
			SwapElements(7);//ставим 7 в ячейку 6
			SwapElements(11);//ставим 8 в ячейку 7
			if ((ints[6] == 7) && (ints[7] == 8))//если 7 и 8 в своих ячейках
			{
				map.push_back(6);//блокируем ячейку 6 (с цифрой 7)
				map.push_back(7); //блокируем ячейку 7 (с цифрой 8)	
			}
			Trasser_Init();
		}
		if (ints[4] == 5 && ints[5] == 6 && ints[6] == 7 && ints[7] == 8)// если все элементы на месте
			break;
		else
		{
			map.erase(find(map.begin(), map.end(), 4));
			map.erase(find(map.begin(), map.end(), 5));
			map.erase(find(map.begin(), map.end(), 6));
			map.erase(find(map.begin(), map.end(), 7)); //снимаем блокировку с элементов строки
			Trasser_Init();
		}
	}	return count_step;
}

int puzle15::Make_Line_End(void)//Функция сборки элементов
{
	//сборка остальных позиций *******************************************************

	if (ints[8] == 9 && ints[9] == 10 && ints[10] == 11 && ints[11] == 12 && ints[12] == 13 && ints[13] == 14 && ints[14] == 15)// Если в раскладке числа 8-15 в ячейках 9-15 т.е не на своих местах
		return count_step; //если все цифры на местах возвращаемся 	

	while (true)
	{
		Trasser_Init();

		if (!(ints[8] == 9 && ints[12] == 13))// Если в раскладке числа 9 и 13 в ячейках 8 и 12 т.е не на своих местах
		{
			if (!(ints[15] == 9 && (ints[10] == 13 || ints[11] == 13)))//проверка на блокированную расстановку
			{
				Set_ElementPosition(9, 15);//ставим 9 в ячейку 15 (правый нижний угол)
				Trasser_Init();
				Set_ElementPosition(13, 8);//ставим 13 в ячейку 8 (место 9)
				map.push_back(8); // блокируем ячейку 8 (с цифрой 13)
				Trasser_Init();
				Set_ElementPosition(9, 9);//ставим 9 в ячейку 9 (место 10)
				map.push_back(9); // блокируем ячейку 9 (с цифрой 9)
				Trasser_Init();
				ZeroPositions(12);
				map.erase(find(map.begin(), map.end(), 8)); // разблокируем ячейку 8 (с цифрой 13)
				map.erase(find(map.begin(), map.end(), 9)); // разблокируем ячейку 9 (с цифрой 9)
				SwapElements(8);
				SwapElements(9);
				map.push_back(8); //блокируем ячейку 8 (с цифрой 9)
				map.push_back(12);//блокируем ячейку 12 (с цифрой 13)
				Trasser_Init();
			}
			else
			{
				//map_15[15] = -1; //разблокируем ячейку 15 (с цифрой 9)
				Trasser_Init();
				Set_ElementPosition(13, 8);//ставим 13 в ячейку 8 (место 9)
				map.push_back(8); //блокируем ячейку 8 (с цифрой 13)
				Set_ElementPosition(9, 9);//ставим 9 в ячейку 9 (место 10)
				map.push_back(9); // блокируем ячейку 9 (с цифрой 9)
				ZeroPositions(12);
				map.erase(find(map.begin(), map.end(), 8));
				map.erase(find(map.begin(), map.end(), 9)); // 
				Trasser_Init();
				SwapElements(8);
				SwapElements(9);
				map.push_back(8);  //блокируем ячейку 8 (с цифрой 9)
				map.push_back(9);  //блокируем ячейку 12 (с цифрой 13)
				Trasser_Init();
			}
			if ((ints[8] == 9) && (ints[12] == 13))
				break;
		}// Конец Если в раскладке числа 9 и 13 в ячейках 8 и 12 т.е не на своих местах
	}
	while (true)
	{
		//Set_ElementPosition(10, 9);//ставим 10 в ячейку 9 (место числа 14) Загоняем "10" сначала на место "14"
		Set_ElementPosition(10, 15);//ставим 10 в ячейку 15 затем ее в правый нижний угол, чтобы выстроить правильную последовательность
		//if (ints[15] != 11)
		//Set_ElementPosition(11, 15);
		//Set_ElementPosition(10, 15);
		map.push_back(15);
		//Set_ElementPosition(12, 14);
		Set_ElementPosition(11, 14);//ставим 11 в ячейку 14 
		//if (ints[11] != 10)
		map.erase(find(map.begin(), map.end(), 15));
		Set_ElementPosition(10, 11);//ставим 10 в ячейку 11 
		Set_ElementPosition(11, 15);//ставим 11 в ячейку 15 
		Set_ElementPosition(12, 14);//12 ставим в ячейку 14
		SwapElements(11);
		SwapElements(15);
		SwapElements(14);
		SwapElements(13);
		SwapElements(9);
		SwapElements(10);
		SwapElements(11);
		SwapElements(15);

		if (ints[8] == 9 && ints[9] == 10 && ints[10] == 11 && ints[11] == 12 && ints[12] == 13)
			break;
	}
	return count_step;
}

int puzle15::CoutnSteps(){
	return count_step;
}