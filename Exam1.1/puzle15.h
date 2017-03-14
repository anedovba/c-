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
	list<int> n_block;//������ ������������� ���������
	list<int> close_list;
	list<int> map;//������ ��������� �� ������ ����� � ������������� ���������
	vector <int> mass_a;/*������ ��������� �������� [0]=�����,[1]=������,[2]=������,[3]=�����
						   (���� ����� ��� ����� ��� �����������, �� �������� -1, ���� ���� �� ����� ������)*/
	vector <int> trassa;//������ ����� ��������
		struct Cell//��������� ������ ��������� ������ ��� ��������  
	{
		int F, G, H, Direct, Poz;/*F - ��������� ��������� ������������,
								 G-��������� ������������ �� ��������� ����� A � ������ ������, ������ ���������� ���� � ���� ������. ,
								 H-��������� ��������� ������������ �� ������ ������ �� �������, �� ���� ����� B.,
								 Direct-����������� ������������ ,
								 Poz- ������� �������� */

	};
	vector <Cell> open_list;//������ �������� ��� ����������� ���������
	int Min_F;//����������� ��������� �������� F
	
	int count_step;//���-�� ����� ��� ������� �����������
	

public:
	puzle15();
	puzle15(vector<int> ints);
	~puzle15();
	void NewFile();//�������� �������� � �����
	void Print();//����� �������� �� �����
	void PrintCopy();//����� �� ����� �������� ������� ������� ����������� �������
	bool Check();//�������� ����������� ������� �����������
	int Epmty();//����� ������ ������
	void Move(char);//�������� ������ ������
	void Moving(char);//���������� ����������� ��������
	bool FieldIsCorrect();//�������� �� ������ �������
	void Trasser_Init(void); //������������� �������� ��� ��������
	int FindElements(int); //������� ����� ������� �����
	int Steps(int, int);//������� ����� ����� � �� ����� ����� � ������
	bool Check_Block_Position(int);//�������� ������������� �� ������ ������� � ������� ������������� ��������� n_block
	int Trasser_Area(static int aa);//��������� �����  
	int Trass_Parent(int parent); //��������� ����� ����� ��������
	void Trasser_patch(int, int);//������� ������ �� ����� � � ����� � (�������� �*)
	void SwapElements(int num); //������� ����� ������� ��������� ���� ������ ������ �����
	void ZeroPositions(int n); //������� �������� ������ ������ � ����� ������ �������
	void Set_ElementPosition(int, int);//��������� ����� � ������ �������
	int Make_Line_1(void);//������ ������� ����  
	int Make_Line_2(void);//������ 2-�� ����
	int Make_Line_End(void);//������ ��������� �����
	int CoutnSteps();


};

