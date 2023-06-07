#include<iostream>
#include"mylib.h"
#include<string>
#include"Front.h"
#include"Flank.h"
#include"LongRange.h"
#include"Powder.h"
#include"Solider.h"
#include"Spear.h"
#include"Sword.h"
#include"Hop.h"
#include<algorithm>
using namespace std;



//global variable
int gx = 50, gy = 5;
#define screen_width 120
#define sreen_height 30

void Box(int, int, int, int, int, int, string);
void Menu(int, int, int, int, int, int, string[], int);



class Formation
{
public:
	Front a;
	LongRange b;
	Flank leftFlank;
	Flank rightFlank;
	void EnterInitialStat();
	void ShowFormation();
};

vector<NonPowder*>input;

void Option()
{
	gotoXY(screen_width/2+5, 15); cout << " ------------------------------------ ";
	gotoXY(screen_width/2+5, 16); cout << " |    Press any key to go back menu  | ";
	gotoXY(screen_width/2+5, 17); cout << " ------------------------------------";
	_getch();
}
void Instruction()
{
	system("cls");
	for (int i = screen_width / 3 - 3; i < screen_width-screen_width/10; ++i)
	{
		gotoXY(i, 12);
		cout << '-';
		gotoXY(i, 23);
		cout << '-';
	}
	for (int i = 13; i <= 22; ++i)
	{
		gotoXY(36,i);
		cout << char(179);//thanh dung trong ma ascii
		gotoXY(screen_width-screen_width/10,i);
		cout << char(179);
	}
	gotoXY(screen_width/3,15); cout << "Instructions";
	gotoXY(screen_width / 3, 16); cout << "----------------";
	gotoXY(screen_width / 3, 17); cout << " Add solider to specified line by choosing '1'->'4'.";
	gotoXY(screen_width / 3, 18); cout << " Press '5'->'8' respectively to see current specified line outlook ";
	gotoXY(screen_width / 3, 19); cout << " Press '9' to see full formation";
	gotoXY(screen_width / 3, 20); cout << " Press the other key to exit";
	gotoXY(screen_width / 3, 21); cout << " Press any key to go back to menu";
	_getch();
}
int main()
{
	ShowCur(0);

	string list[10] = { "1. Add Solider to FrontLine" ,"2. Add Solider to LongRange Line" ,"3. Add Solider to Left Flank line"
						,"4. Add Solider to Right Flank" ,"5. Show FrontLine" ,"6. Show LongRange"
						,"7.Show Left Flank.","8.Show Right Flank.","9.Show formation."
						,"Select option: " };

	Formation X;
	ShowCur(0);
	ShowCursor(0);
	Box(gx, gy, 35, 2, 11, 1, "		SOLIDER GAME");

	SetColor(15);
	Sleep(1000);
	system("cls");
	gotoXY(10, 6);
	cout << "ENTER INITIAL STATATISTIC FOR THE 4 LINE\n";
	cout << "\n-------------------------------------------\n";
	X.EnterInitialStat();

	Instruction();
	do
	{
		system("cls");
		gotoXY(gx + 15, gy - 1); cout << "MENU\n";
		int op;
		Menu(gx, gy, 35, 2, 11, 1, list, 10);
		op = _getch();
		Sleep(200);
		SetColor(15);
		cout << char(op);

		if (op == '1')
		{
			system("cls");
			cout << "\nADD SOLIDER TO FRONTLINE\n";
			X.a.AddSolidertoLine();
			Option();
		}
		else if (op == '2')
		{
			system("cls");
			cout << "\nADD SOLIDER TO LONGRANGELINE\n";
			X.b.AddSolidertoLine();
			Option();
		}
		else if (op == '3')
		{
			system("cls");
			cout << "\nADD SOLIDER TO LEFT FLANK\n";
			X.leftFlank.AddSolidertoLine();
			Option();
		}
		else if (op == '4')
		{
			system("cls");
			cout << "\nADD SOLIDER TO RIGHT FLANK\n";
			X.rightFlank.AddSolidertoLine();
			Option();
		}
		else if (op == '5')
		{
			system("cls");
			cout << "CURRENT FRONTLINE\n";
			X.a.Display();
			Option();
		}
		else if (op == '6')
		{
			system("cls");
			cout << "CURRENT LONGRANGE\n";
			X.b.Display();
			Option();
		}
		else if (op == '7')
		{
			system("cls");
			cout << "CURRENT LEFT FLANK\n";
			X.leftFlank.Display();
			Option();
		}
		else if (op == '8')
		{
			system("cls");
			cout << "CURRENT RIGHT FLANK\n";
			X.rightFlank.Display();
			Option();
		}
		else if (op == '9')
		{
			system("cls");
			gotoXY(23, 19);
			cout << "FORMATION\n";
			X.ShowFormation();
			Option();
		}
		else exit(0);
	}while (1);
	_getch();

}


void Box(int x, int y, int w, int h, int index_color, int index_textcolor, string content)
{
	//fill the area with the color
	textcolor(index_textcolor);
	for (int ix = x + 1; ix <= x + w - 1; ++ix)
	{
		for (int iy = y; iy <= y + h - 1; ++iy)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}

	//content of in the box
	SetColor(7);
	gotoXY(x + 1, y + 1);
	cout << content;

	//draw the border of menu
	textcolor(1);
	SetColor(index_color);
	for (int ix = x; ix < x + w; ++ix)
	{
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + h);
		cout << char(196);
	}
	for (int iy = y; iy < y + h; ++iy)
	{
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + w, iy);
		cout << char(179);
	}
	gotoXY(x, y); cout << char(218);
	gotoXY(x + w, y); cout << char(191);
	gotoXY(x, y + h); cout << char(192);
	gotoXY(x + w, y + h); cout << char(217);
}
void Menu(int x, int y, int w, int h, int index_color, int index_textcolor, string content[], int Cols)
{
	int count = 0;
	for (int i = 0; i < Cols - 1; ++i)
	{
		Box(x, y + i * 2, w, h, index_color, index_textcolor, content[count++]);
		if (i != 0)
		{
			gotoXY(x, y + (i * 2)); cout << char(195);
			gotoXY(x + w, y + i * 2); cout << char(180);
		}
	}
	//Deal with showing the cursor next to select option;
	int last = (Cols - 1);
	Box(x, y + last * 2, w, h, index_color, index_textcolor, content[count++]);
	gotoXY(x, y + (last * 2)); cout << char(195);
	gotoXY(x + w, y + last * 2); cout << char(180);
	gotoXY(x + 15, y + last * 2 + 1);
}
void Formation::EnterInitialStat()
{
	cout << "Front Line (maximum 240)\n";
	a.EnterInitialStat();
	cout << "\n---------------------------\n";
	cout << "LongRange Line (maximum 96)\n";
	b.EnterInitialStat();
	cout << "\n-----------------------------\n";
	
	//Left flank.
	cout << "Left Flank (maximum 60)\n";
	cout << "Enter number of Sword: ";
	cin >> leftFlank.FLnumSword;
	cout << "Enter number of Spear: ";
	cin >> leftFlank.FLnumSpear;

	for (int i = 0; i <leftFlank.FLnumSword;++i)
		input.push_back(new Sword);
	for (int i = 0; i <leftFlank.FLnumSpear; ++i)
		input.push_back(new Spear);

	leftFlank.arrange(input);
	
	cout << "\n--------------------------------\n";
	cout << "Right Flank (maximum 60)\n";
	cout << "Enter number of Sword: ";
	cin >> rightFlank.FLnumSword;
	cout << "Enter number of Spear: ";
	cin >> rightFlank.FLnumSpear;

	input.clear();
	for (int i = 0; i < rightFlank.FLnumSword; ++i)
		input.push_back(new Sword);
	for (int i = 0; i < rightFlank.FLnumSpear; ++i)
		input.push_back(new Spear);

	rightFlank.arrange(input);
	
}
void Formation::ShowFormation()
{
	const int start = 15;

	//Show formation of LongRange
	int curLongRange = 20;
	int ok = 1;
	int temp = 0;
	int numLR = 0;
	for (int i = 0; i < 12; ++i)
	{
		gotoXY(start + 8, curLongRange++);
		for (int j = 0; j < 8; ++j)
		{
			if (b.all[i][j])
			{
				b.all[i][j]->DrawSolider();
				cout << ' ';
				++numLR;
			}
			else if (ok)
			{
				temp = curLongRange;
				ok = 0;
			}
		}
	}
	if (numLR == 96 && ok) temp = curLongRange;
	//Show formation of Front
	int curFR = temp;
	for (int i = 0; i < 30; ++i)
	{
		gotoXY(start + 8, curFR++);
		for (int j = 0; j < 8; ++j)
		{
			if (a.all[i][j])
			{
				a.all[i][j]->DrawSolider();
				cout << ' ';
			}
		}
	}

	//showformation of left Flank
	int curFlankleft = temp;
	for (int i = 0; i < 20; ++i)
	{
		gotoXY(start + 2, curFlankleft++);
		for (int j = 0; j < 3; ++j)
		{
			if (leftFlank.all[i][j])
			{
				leftFlank.all[i][j]->DrawSolider();
			}
			else cout << ' ';
		}
	}

	//show formation of right Flank
	int curFlankright = temp;
	for (int i = 0; i <20; ++i)
	{
		gotoXY(start + 25, curFlankright++);
		for (int j = 0; j < 3; ++j)
		{
			if (rightFlank.all[i][j])
			{
				rightFlank.all[i][j]->DrawSolider();
			}
			else cout << ' ';
		}
	}
}
