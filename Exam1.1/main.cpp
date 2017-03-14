#include "puzle15.h"

using namespace std;
int main(){
	cout << "\tLet's start!\n" << endl;
	puzle15 A;
	A.NewFile();//чтение с файла
	A.Print();//выведение на экран кост€шек
	if (A.Check())//проверка на возможность решени€ головоломки
		return 0;
	int key;
	cout << "If you want to solve yourself - press 0, if automatically - press 1.\n";
	cin >> key;
	switch (key)
	{
	case 0: 
	{
		char c;
		while (!A.FieldIsCorrect()){
			
			cout << "Let's play, enter key  (Up-8, Down-2, Left-4, Right-6, Escape-0)\n";
			
			c = _getche();
			A.Moving(c);
			system("cls");
			A.PrintCopy();
		}

		cout << "\n\nCongratulations! Press Enter to exit!\n"; //ѕоздравление игрока
	}
		break;

	case 1:
	{
		A.Make_Line_1(); //сложение первой строки
		A.Make_Line_2();//сложение второй строки
		A.Make_Line_End();//сложение третьей строки
		cout << "\n\tTotal " << A.CoutnSteps() << " steps\n\n";
		
	}
		break;
	default: 
		cout << "Wrong key!!!\n";
		break;
	}
	

	return 0;
}