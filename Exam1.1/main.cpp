#include "puzle15.h"

using namespace std;
int main(){
	cout << "\tLet's start!\n" << endl;
	puzle15 A;
	A.NewFile();//������ � �����
	A.Print();//��������� �� ����� ��������
	if (A.Check())//�������� �� ����������� ������� �����������
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

		cout << "\n\nCongratulations! Press Enter to exit!\n"; //������������ ������
	}
		break;

	case 1:
	{
		A.Make_Line_1(); //�������� ������ ������
		A.Make_Line_2();//�������� ������ ������
		A.Make_Line_End();//�������� ������� ������
		cout << "\n\tTotal " << A.CoutnSteps() << " steps\n\n";
		
	}
		break;
	default: 
		cout << "Wrong key!!!\n";
		break;
	}
	

	return 0;
}