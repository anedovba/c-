#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random> 
#include <stdlib.h>
#include <windows.h> 
#include <conio.h>
#include <list>
using namespace std;
class puzle15
{
	
	vector <int> ints;
	vector<int> intsCopy;
	list<int> n_block;//список блокированных элементов
	list<int> close_list;
	list<int> map;//список собранных на нужное место и блокированных элементов
	vector <int> mass_a;/*массив окружени€ элемента [0]=слева,[1]=справа,[2]=сверху,[3]=снизу
						   (если р€дом нет €чеек или блокированы, то содержит -1, если есть то номер €чейки)*/
	vector <int> trassa;//массив точек маршрута
		struct Cell//структура €чейки открытого списка дл€ трассера  
	{
		int F, G, H, Direct, Poz;/*F - расчетна€ стоимость передвижени€,
								 G-стоимость передвижени€ из стартовой точки A к данной клетке, следу€ найденному пути к этой клетке. ,
								 H-примерна€ стоимость передвижени€ от данной клетки до целевой, то есть точки B.,
								 Direct-направление передвижени€ ,
								 Poz- позици€ элемента */

	};
	vector <Cell> open_list;//массив открытых при трассировке элементов
	int Min_F;//минимальна€ стоимость маршрута F
	
	int count_step;//кол-во шагов дл€ решени€ головоломки
	

public:
	puzle15();
	puzle15(vector<int> ints);
	~puzle15();
	void NewFile();//загрузка п€тнашек с файла
	void Print();//вывод п€тнашек на экран
	void PrintCopy();//вывод на экран п€тнашек решение которых выполн€етс€ вручную
	bool Check();//проверка возможности решени€ головоломки
	int Epmty();//поиск пустой €чейки
	void Move(char);//движение пустой €чейки
	void Moving(char);//считывание направлени€ движени€
	bool FieldIsCorrect();//проверка на полное решение
	void Trasser_Init(void); //инициализаци€ массивов дл€ трассера
	int FindElements(int); //функци€ поиск позиции числа
	int Steps(int, int);//подсчет числа шагов к от одной точки к другой
	bool Check_Block_Position(int);//проверка заблокирована ли данна€ позици€ в массиве блокированных элементов n_block
	int Trasser_Area(static int aa);//окружение точки  
	int Trass_Parent(int parent); //установка новой точки родител€
	void Trasser_patch(int, int);//создаем машрут из точки ј в точку ¬ (алгоритм ј*)
	void SwapElements(int num); //функци€ обмен местами элементов если пуста€ €чейка р€дом
	void ZeroPositions(int n); //функци€ сдвинуть пустую €чейку в любую нужную позицию
	void Set_ElementPosition(int, int);//поставить число в нужную позицию
	int Make_Line_1(void);//сборка первого р€да  
	int Make_Line_2(void);//сборка 2-го р€да
	int Make_Line_End(void);//сборка остальных полей
	int CoutnSteps();


};

