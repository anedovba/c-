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
	while (!feof(pf))//������� ���������� �����
		{
			count++;
			fgets(s, 4, pf);
		}
		rewind(pf);//��������� ������ �� ������ �����
		str*MAS = new str[count];//������� ������ ������� ����������� �����
		for (int i = 0; i < count; i++)//��������� ������ �������� � �����
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
bool puzle15::Check(){//�������� �� ����������� ������� �����������
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
		return true;//������� �����������
	}
}
int puzle15::Epmty()
{
	for (int i = 0; i<16; i++)
		if (intsCopy[i] == 0)
			return i;
}

void puzle15::Move(char c)//������������ ������� ����
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
	switch (c) //� ����������� �� ������� ������� (�� �� �������������� ����) ������� ��������
	{
	case '4': Move('4'); break; //������ ������� "�����"
	case '8': Move('8'); break; //������ ������� "�����"
	case '6': Move('6'); break; //������ ������� "������"
	case '2': Move('2'); break; //������ ������� "����"
	case '0': exit(0); //������ ������� "Escape"
	}
}
bool puzle15::FieldIsCorrect()
{
	for (int i = 0; i < 15; i++)
		if (intsCopy[i] != i + 1)
			return false; //��� ������ �� ���������� �������������� ������� � ���������� false
	return true;//���� �� ������� �� ������ �������������� - ���� ������� �����
}

void puzle15::Trasser_Init(void) //������������� �������� ��� ��������
{
	close_list.clear();
	for (int i = 0; i < 16; i++)//������������� �������� (-1)
	{

		if (!map.empty())//���� � ������� ���� ��������� ��� ���� ������� �� ��������� ��� � � �������� ����
			close_list.insert(close_list.end(), map.begin(), map.end());//��������� ������� �� ������� ������ � ������ �������� ��� ����������� ���������

		if (!n_block.empty())//���� � ������� ���������� ��� ���� ������� �� ��������� ��� � �������� ����
			close_list.insert(close_list.end(), n_block.begin(), n_block.end());//��������� ������� �� ������� ���������� � ������ �������� ��� ����������� ���������

		trassa[i] = -1;//������ ����� ��������
		//�������� ������ �������� ������ �����
		open_list[i].F = 0;
		open_list[i].G = 0;
		open_list[i].H = 0;
		open_list[i].Poz = 0;
	}
	Min_F = 100;
}
int puzle15::FindElements(int n) //������� ����� ������� �����
{
	for (int i = 0; i<16; i++)
		if (ints[i] == n)
			return i;
}

int puzle15::Steps(int a, int b)//������� ����� ����� � �� ����� ����� � ������
{
	int step = 0, tmp;
	if (b<a)
	{
		swap(a, b);
	}
	while (a != b)
	{
		if (b>a&&a / 4 != b / 4) //���� b ������ � � ��� � ������ �������
		{
			a = a + 4;//��������� �� ������ ������
			step++;//������ ���
		}
		if (b>a&&a / 4 == b / 4) //���� b ������ a � ��� � ����� ������
		{
			a++;//��������� �� ������ ������
			step++;//������ ���
		}
		if (b<a)
		{
			a--;
			step++;
		}
	}
	return step;
}

bool puzle15::Check_Block_Position(int p)//�������� ������������� �� ������ ������� � ������� ������������� ��������� n_block
{
	if (find(close_list.begin(), close_list.end(), p) != close_list.end())//��������� �������� � �������� ������ (���� ������������ �� ������� ������� �������� ���� ������=�)
		return true;//����������
	else
		return false;//�� ����������
}

int puzle15::Trasser_Area(static int aa)
{
	int d = 0;//���-�� ����������� �� ���� �����
	int _r;
	if ((aa - 1) / 4 == (aa / 4))//���� �� ����� ����� ������� �� ��� �� ������
	{
		if (!Check_Block_Position(aa - 1))//���� ������� ����� �� ����������
			mass_a[0] = aa - 1; //���������� �� �� ����������
		else
			mass_a[0] = -1; //�� ����������, �� ����������
	}
	else
		mass_a[0] = -1;//�������� ����� ��� �� �� ����� �������� 

	if ((aa + 1) <= 15 && (aa + 1) / 4 == aa / 4)//���� �� ����� ������ ������� �� ��� �� ������
	{
		if (!Check_Block_Position(aa + 1))//���� ������� ������ �� ����������
			mass_a[1] = aa + 1; //���������� �� �� ����������
		else
			mass_a[1] = -1;	//�� ����������, �� ����������	
	}
	else
		mass_a[1] = -1;//�������� ������ ��� �� �� ������ �������� 

	if ((aa - 4) >= 0)//���� �� ��� ���� ��������� ������� ����
	{
		if (!Check_Block_Position(aa - 4))//���� ������� ������ �� ����������
			mass_a[2] = aa - 4;//���������� �� �� ����������
		else
			mass_a[2] = -1;	//�� ����������, �� ����������	
	}
	else
		mass_a[2] = -1;//�������� ������ ��� �� �� ������� �������� 

	if ((aa + 4) <= 15)//���� �� ��� ���� ��������� ������� ����
	{
		if (!Check_Block_Position(aa + 4))//���� ������� ����� �� ����������
			mass_a[3] = aa + 4;//���������� �� �� ����������
		else
			mass_a[3] = -1;	//�� ����������, �� ����������	
	}
	else
		mass_a[3] = -1;//�������� ����� ��� �� �� ������ �������� 

	for (_r = 0; _r<4; _r++)//������� ����� �����������
	{
		if (mass_a[_r] != -1)
			d++;
	}

	return d;
}

int puzle15::Trass_Parent(int parent) //������� ��������� ����� ����� �������� 
{
	int i, el;

	for (i = 0; i<4; i++)
	{
		el = mass_a[i];
		if (el != -1)
		{
			if (Min_F >= open_list[el].F)
			{
				if (open_list[el].Direct != 0)//��������� ���������� � ��������
				{
					Min_F = open_list[el].F;
					parent = open_list[el].Poz;
				}
			}
		}
	}
	return parent;
}

void puzle15::Trasser_patch(int start, int finish)//������� ������ �� ����� � � ����� � (�������� �*)
{
	int rod = start; //��������� �������� - ��������� �����
	int old_rod = start;//���������� �������� - ��������� �����
	int count_rod = 0;
	int i;
	int direct = 0; //��������� ����������� ����������� �� ������ �����
	int count_point = 0;//������� ����� ��������
	int n_step; //���-�� ����������� � ������ ����� �� ���������

	open_list[start].Poz = start; //������� ��������
	open_list[start].G = 0;//G = ��������� ������������ �� ��������� ����� A � ������ ������, ������ ���������� ���� � ���� ������.
	//(����� ������� ��� ��������� ������������ �� 1 ������� =10)
	open_list[start].H = Steps(start, finish) * 10;/*H = ��������� ��������� ������������ �� ������ ������ �� �������, �� ���� ����� B.
												   ��� ������ �������� ������������� ��������.*/
	//��������� H ��������� � ������� ���������� �������������� ���������� � ����� �, 
	//�������� ������ �� ����������� � ���������, ��������� ��� ����������� �� ����.
	open_list[start].F = open_list[start].G + open_list[start].H; //��������� F ��� ������ ������ ����������� ������� ������������� G � H.
	//open_list[start].Dst = abs(finish-start); //�������� ����� ��������� ������ � ��������

	if (!n_block.empty())//���������� � �������� ������ ��������� �� ������ ���������� 
	{
		close_list.insert(close_list.end(), n_block.begin(), n_block.end());//��������� ��� � �������� ������
	}

	open_list[finish].Poz = finish;//������� � �������� ������ �������� �����
	open_list[finish].H = -1;//������������� �������� �����, ����� �� ����� ����� � ����

	while (open_list[finish].H != 0) //������ ������� ���� �� �������� �������� ����� �.� ��� H=0 �� ��������� � ���. �����
	{
		//count_step++;
		direct = Trasser_Area(rod);//��������� ����� mass_a ��������� ������������ ����� � ���������� ����� ����������� �� ������������ �����
		close_list.push_back(rod); //������� ��������� ����� � �������� ������

		for (i = 0; i<4; i++)//��������� open_list ������ �� ������� ��������� ��������
		{
			n_step = 10;//������������� �������� �������� �� 1 ���
			int ar = mass_a[i];//��������� ������� ��������� � open_list (� ���� ������� [0] -����� ������ [1]-����� ����� [2]-����� ������ [3]-����� �����)
			if (ar != -1)//���� ������� = -1 �� �������� ����� � ����� ���� ������� ��� ���� ��� ������������� � close_list
			{
				open_list[ar].Poz = ar; //������� ��������

				for (int c = 0; c<16; c++) //��������� ��� ��������� ����� �������� � ������� ������� ����� �� ��� ������
				{
					if (trassa[c] != -1)
						n_step += 10;//��������� ��������� ������������ �� ����� ������ =10 � ����� �� �����������
				}
				open_list[ar].G = n_step; //������� ��������� ����������� �� ��������� � ��� ������
				open_list[ar].H = ((Steps(ar, finish)) * 10);//������� ��������� ����������� �� ������ ������ � ��������
				open_list[ar].F = open_list[ar].G + open_list[ar].H;//��������� F=G+H;
				open_list[ar].Direct = direct;//���������� ���-�� ����������� ����������� �� ������������ �����;
			}
		}
		old_rod = rod;
		rod = Trass_Parent(rod);//�������� �������� 

		if (count_point<16 && old_rod != rod)//���� ������� ������ �� ��������� ������ ������� �������� � ������ � ����� �������� �� ���������
		{
			trassa[count_point] = rod;//���������� ����� �������� � ������
			count_point++;//����������� ������� ����� ��������
			Min_F = 100;
		}
		if (old_rod == rod)//���� ������ � ����� �������� ��������� ����� �� ������������
			count_rod++;
		if (count_rod == 10)
		{
			break;
		}

		if (count_point >= 16)//���� �������� ������
		{
			cout << "������������ trassa ���� Trasser" << endl;
			break;
		}
	}//End while
}

void puzle15::SwapElements(int num) //������� ����� ������� ��������� ���� ������ ������ �����
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
	if (num == zero + 1 || num == zero - 1 || num == zero - 4 || num == zero + 4)//���� ����� � ��������� �� ������ num ��������� ������ 
	{
		ints[zero] = Num;//���������� �������� �������� � ������ ��� ��� 0
		ints[num] = 0;	//���������� 0 � ������ ��� ��� �������
		count_step++;
		system("cls");
		cout << "\tNext step\n\n";
		Print();
		system("pause");

	}
}

void puzle15::ZeroPositions(int n) //������� �������� ������ ������ � ����� ������ �������
{
	int p_zero = FindElements(0);//������� ����� "0" � �������
	int i;
	if (p_zero == n)//���� ���� ��� � ������ ������� �� �������
		return;

	Trasser_patch(p_zero, n);//������� ������� �� ��������� 0(p_zero) � ��������� �����(n)

	for (i = 0; i<16; i++)//������� ����� ��������
	{
		if (trassa[i] != -1)//���� ���� ����� (����� �� ������ -1)

		{
			SwapElements(trassa[i]);//������ 0 � ��������� ��������
		}
	}
	Trasser_Init();

}

void puzle15::Set_ElementPosition(int number, int ni) //��������� ����� � ������ �������
{
	int poz_number = FindElements(number);
	int n_column = ni % 4;//��������� ����� ������� ��� �������
	int n_line = ni / 4;//��������� ����� ������ ��� �������
	int el_column;//����� ������� ��� ��������
	int el_line;//����� ������ ��� ��������

	if (ni == poz_number)//���� ������� �� ����� �� �������
		return;

	while (ni != poz_number)//��������� ���� �� �������� ������ �������
	{
		el_column = poz_number % 4;//��������� ����� ������� ��� ��������
		el_line = poz_number / 4;//��������� ����� ������ ��� ��������

		n_block.push_back(poz_number);//��������� ��� ����� ����� ����������������� �������
		if (el_column<n_column)//���� ������� �������� ����� �� ������ �������
		{

			ZeroPositions(int(poz_number + 1));//������������� ������ ������ ������
			SwapElements(poz_number); //������ ������� � ������ �������
			//n_block.erase(find(n_block.begin(), n_block.end(), poz_number));//������� ���������� ����� ����� ���������������� �������
		}

		if (el_column>n_column)//���� ������� �������� ������ �� ������ �������
		{
			//n_block.push_back(poz_number);//��������� ��� ����� ����� ����������������� �������
			ZeroPositions(int(poz_number - 1));//������������� ������ ������ ����� 
			SwapElements(poz_number); //������ ������� � ������ ������� 
			//n_block.erase(find(n_block.begin(), n_block.end(), poz_number));//������� ���������� ����� ����� ���������������� �������

		}

		if ((el_column == n_column) && (el_line>n_line))//���� ������� ��������� � ������� �� ��� ������� ���� ������ ������
		{
			//n_block.push_back(poz_number);//��������� ��� ����� ����� ����������������� �������
			ZeroPositions(int(poz_number - 4));//������������� ������ ������ ������
			SwapElements(poz_number); //������ ������� � ������ �������
			//n_block.erase(find(n_block.begin(), n_block.end(), poz_number));//������� ���������� ����� ����� ���������������� �������
		}
		if ((el_column == n_column) && (el_line<n_line))//���� ������� ��������� � ������� �� ��� ������� ���� ������ ������
		{
			//n_block.push_back(poz_number);//��������� ��� ����� ����� ����������������� �������
			ZeroPositions(int(poz_number + 4));//������������� ������ ������ �����
			SwapElements(poz_number); //������ ������� � ������ �������

		}
		n_block.erase(find(n_block.begin(), n_block.end(), poz_number));//������� ���������� ����� ����� ���������������� �������
		Trasser_Init();//������������� �������� �����������
		poz_number = FindElements(number);

	}
}

int puzle15::Make_Line_1(void)
{
	Trasser_Init();//������������� ��������
	if (ints[0] == 1 && ints[1] == 2 && ints[2] == 3 && ints[3] == 4)//���� 1,2,3,4 �� ����� ������ �� ��� �������
	{
		map.push_back(0);
		map.push_back(1);
		map.push_back(2);
		map.push_back(3);
		//��������� ���� ��� �� ������
		return count_step; //������������ ��� �������!!!!
	}
	//������ 1-�� ���� **************************************************************************************

	Set_ElementPosition(1, 0);
	if (ints[0] == 1)
		map.push_back(0); //��������� ������ 0 (� ������ 1)
	Trasser_Init();
	Set_ElementPosition(2, 1);
	if (ints[1] == 2)
		map.push_back(1); //��������� ������ 1 (� ������ 2)
	Trasser_Init();
	if (ints[0] == 1 && ints[1] == 2)//���� ������ � ����a� ������ �� �����
	{

		while (true){
			Trasser_Init();
			Set_ElementPosition(4, 11);


			Set_ElementPosition(3, 3);
			if (ints[3] == 3)//���� ������ 3 �� �����
				map.push_back(3); //��������� ������ 3 (� ������ 3)
			Trasser_Init();

			Set_ElementPosition(4, 7);//������ 4 � ������ 7
			if (ints[7] == 4)
				map.push_back(7); //��������� ������ 7 (� ������ 4)
			Trasser_Init();

			if ((ints[3] == 3) && (ints[7] == 4))
			{
				ZeroPositions(2);//������ ������ ������ �� ������ 2
				map.erase(find(map.begin(), map.end(), 3)); //������� ���������� � ������ 3 (� ������ 3)
				map.erase(find(map.begin(), map.end(), 7)); //������� ���������� � ������ 7 (� ������ 4)
				Trasser_Init();
				SwapElements(3);//������ 3 � ������ 2

				SwapElements(7);//������ 4 � ������ 3

				if ((ints[2] == 3) && (ints[3] == 4))//���� 3 � 4 � ����� �������
				{
					map.push_back(2); //��������� ������ 2 (� ������ 3)
					map.push_back(3); //��������� ������ 3 (� ������ 4)
					Trasser_Init();
					break;
				}
				else
				{
					map.erase(find(map.begin(), map.end(), 2)); //������������ ������ 2 (� ������ 3)
					map.erase(find(map.begin(), map.end(), 3)); //������������ ������ 3 (� ������ 4)
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
	if (ints[4] == 5 && ints[5] == 6 && ints[6] == 7 && ints[7] == 8)//���� �������� 5,6,7,8 �� ����� ������
	{
		map.push_back(4);
		map.push_back(5);
		map.push_back(6);
		map.push_back(7); //��������� ���� ���, �� ������
		return count_step; //������������ ��� �������!!!!
	}
	Trasser_Init();//������������� ��������
	//������ 2-�� ���� *******************************************************
	// 
	while (true)//��������� ���� �������� 5,6,7,8 �� ����� �� ����� ������
	{
		Set_ElementPosition(5, 4);
		if (ints[4] == 5)
			map.push_back(4); //��������� ������ 4 (� ������ 5)
		Trasser_Init();
		Set_ElementPosition(6, 5);
		if (ints[5] == 6)
			map.push_back(5);//��������� ������ 5 (� ������ 6)
		Trasser_Init();
		if (ints[4] == 5 && ints[5] == 6)//���� ����� 5 � 6 �� ����� �� �����
		{
			while (ints[7] != 7)
			{
				Set_ElementPosition(7, 7);//������� �� ���������������� 7
				if (ints[7] == 7)
					map.push_back(7);//��������� ������ 7 (� ������ 7)
				Trasser_Init();
				if (ints[6] == 8)//���� ����� 8 �������� ���� ����������� �� ������� 6 ����� �������� �� � ��� 8, ���� ����� �� �������, �� ��� ������������� � ���� � �� ���������� ����� ������
				{
					//map.erase(find(map.begin(), map.end(), 6));
					map.erase(find(map.begin(), map.end(), 7));
					Trasser_Init();
					Set_ElementPosition(8, 14);
					Set_ElementPosition(7, 7);
					map.push_back(7);//��������� ������ 7 (� ������ 7)
				}
			}

			Set_ElementPosition(8, 11);//������ 8 � ������ 11
			if (ints[11] == 8)
				map.push_back(11);//��������� ������ 11 (� ������ 8)
			Trasser_Init();
			ZeroPositions(6);//������ ������ ������ �� ������ 6 //����� ����� ������ ������� �������� ������
			if (find(map.begin(), map.end(), 7) != map.end())
				map.erase(find(map.begin(), map.end(), 7)); //������� ���������� � ������ 7 (� ������ 7)
			map.erase(find(map.begin(), map.end(), 11)); //������� ���������� � ������ 11 (� ������ 8)
			Trasser_Init();
			SwapElements(7);//������ 7 � ������ 6
			SwapElements(11);//������ 8 � ������ 7
			if ((ints[6] == 7) && (ints[7] == 8))//���� 7 � 8 � ����� �������
			{
				map.push_back(6);//��������� ������ 6 (� ������ 7)
				map.push_back(7); //��������� ������ 7 (� ������ 8)	
			}
			Trasser_Init();
		}
		if (ints[4] == 5 && ints[5] == 6 && ints[6] == 7 && ints[7] == 8)// ���� ��� �������� �� �����
			break;
		else
		{
			map.erase(find(map.begin(), map.end(), 4));
			map.erase(find(map.begin(), map.end(), 5));
			map.erase(find(map.begin(), map.end(), 6));
			map.erase(find(map.begin(), map.end(), 7)); //������� ���������� � ��������� ������
			Trasser_Init();
		}
	}	return count_step;
}

int puzle15::Make_Line_End(void)//������� ������ ���������
{
	//������ ��������� ������� *******************************************************

	if (ints[8] == 9 && ints[9] == 10 && ints[10] == 11 && ints[11] == 12 && ints[12] == 13 && ints[13] == 14 && ints[14] == 15)// ���� � ��������� ����� 8-15 � ������� 9-15 �.� �� �� ����� ������
		return count_step; //���� ��� ����� �� ������ ������������ 	

	while (true)
	{
		Trasser_Init();

		if (!(ints[8] == 9 && ints[12] == 13))// ���� � ��������� ����� 9 � 13 � ������� 8 � 12 �.� �� �� ����� ������
		{
			if (!(ints[15] == 9 && (ints[10] == 13 || ints[11] == 13)))//�������� �� ������������� �����������
			{
				Set_ElementPosition(9, 15);//������ 9 � ������ 15 (������ ������ ����)
				Trasser_Init();
				Set_ElementPosition(13, 8);//������ 13 � ������ 8 (����� 9)
				map.push_back(8); // ��������� ������ 8 (� ������ 13)
				Trasser_Init();
				Set_ElementPosition(9, 9);//������ 9 � ������ 9 (����� 10)
				map.push_back(9); // ��������� ������ 9 (� ������ 9)
				Trasser_Init();
				ZeroPositions(12);
				map.erase(find(map.begin(), map.end(), 8)); // ������������ ������ 8 (� ������ 13)
				map.erase(find(map.begin(), map.end(), 9)); // ������������ ������ 9 (� ������ 9)
				SwapElements(8);
				SwapElements(9);
				map.push_back(8); //��������� ������ 8 (� ������ 9)
				map.push_back(12);//��������� ������ 12 (� ������ 13)
				Trasser_Init();
			}
			else
			{
				//map_15[15] = -1; //������������ ������ 15 (� ������ 9)
				Trasser_Init();
				Set_ElementPosition(13, 8);//������ 13 � ������ 8 (����� 9)
				map.push_back(8); //��������� ������ 8 (� ������ 13)
				Set_ElementPosition(9, 9);//������ 9 � ������ 9 (����� 10)
				map.push_back(9); // ��������� ������ 9 (� ������ 9)
				ZeroPositions(12);
				map.erase(find(map.begin(), map.end(), 8));
				map.erase(find(map.begin(), map.end(), 9)); // 
				Trasser_Init();
				SwapElements(8);
				SwapElements(9);
				map.push_back(8);  //��������� ������ 8 (� ������ 9)
				map.push_back(9);  //��������� ������ 12 (� ������ 13)
				Trasser_Init();
			}
			if ((ints[8] == 9) && (ints[12] == 13))
				break;
		}// ����� ���� � ��������� ����� 9 � 13 � ������� 8 � 12 �.� �� �� ����� ������
	}
	while (true)
	{
		//Set_ElementPosition(10, 9);//������ 10 � ������ 9 (����� ����� 14) �������� "10" ������� �� ����� "14"
		Set_ElementPosition(10, 15);//������ 10 � ������ 15 ����� �� � ������ ������ ����, ����� ��������� ���������� ������������������
		//if (ints[15] != 11)
		//Set_ElementPosition(11, 15);
		//Set_ElementPosition(10, 15);
		map.push_back(15);
		//Set_ElementPosition(12, 14);
		Set_ElementPosition(11, 14);//������ 11 � ������ 14 
		//if (ints[11] != 10)
		map.erase(find(map.begin(), map.end(), 15));
		Set_ElementPosition(10, 11);//������ 10 � ������ 11 
		Set_ElementPosition(11, 15);//������ 11 � ������ 15 
		Set_ElementPosition(12, 14);//12 ������ � ������ 14
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