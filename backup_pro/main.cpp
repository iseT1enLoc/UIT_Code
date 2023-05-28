#include"Front.h"
#include"Flank.h"
#include"LongRange.h"
#include"Powder.h"
#include"Solider.h"
#include"Spear.h"
#include"Sword.h"
#include"Hop.h"
#include"myLib.h"

class Formation
{
public:
	Front a;
	LongRange b;
	Flank leftFlank=Flank(true);
	Flank rightFlank = Flank(false);
	void EnterInitialStat();
	void ShowFormation();
};
int main()
{
	Formation X;
	ShowCur(0);
	gotoXY(10, 5); cout << " -------------------------- ";
	gotoXY(10, 6); cout << " |        SOLIDER GAME      | ";
	gotoXY(10, 7); cout << " --------------------------";

	Sleep(1000);
	system("cls");
	gotoXY(10, 6);
	cout << "ENTER INITIAL STATATISTIC FOR THE 4 LINE\n";
	X.EnterInitialStat();

	while (1)
	{
		system("cls");
		Sleep(100);
		gotoXY(10, 9); cout << "1. Add Solider to FrontLine";
		gotoXY(10, 10); cout << "2. Add Solider to LongRange Line";
		gotoXY(10, 11); cout << "3. Add Solider to Flank line";
		gotoXY(10, 12); cout << "4. Show FrontLine";
		gotoXY(10, 13); cout << "5. Show LongRange";
		gotoXY(10, 14); cout << "6.Show Left Flank.";
		gotoXY(10, 15); cout << "7.Show Right Flank.";
		gotoXY(10, 16); cout << "8.Show formation.";
		gotoXY(10, 17); cout << "Select option: ";
		char op = _getche();
		if (op == '1')
		{
			system("cls");
			gotoXY(10, 6);
			cout << "\nADD SOLIDER TO FRONTLINE\n";
			X.a.AddSolidertoLine();
		}
		else if (op == '2')
		{
			system("cls");
			gotoXY(10, 6);
			cout << "\nADD SOLIDER TO LONGRANGELINE\n";
			X.b.AddSolidertoLine();
		}
		else if (op == '3')
		{
			system("cls");
			cout << "Done";
		}
		else if (op == '4')
		{
			system("cls");
			cout << "CURRENT FRONTLINE\n";
			X.a.Display();
			Sleep(2500);
		}
		else if (op == '5')
		{
			system("cls");
			cout << "CURRENT LONGRANGE\n";
			X.b.Display();
			Sleep(2500);
		}
		else if (op == '6')
		{
			system("cls");
			cout << "CURRENT LEFT FLANK\n";
			X.leftFlank.Display();
			Sleep(2500);
		}
		else if (op == '7')
		{
			system("cls");
			cout << "CURRENT RIGHT FLANK\n";
			X.rightFlank.Display();
			Sleep(2500);
		}
		else if (op == '8')
		{
			system("cls");
			gotoXY(23,15);
			cout << "FORMATION\n";
			X.ShowFormation();
			Sleep(5000);
		}
		else exit(0);
	}
	_getch();

}
void Formation::EnterInitialStat()
{
	cout << "Front Line\n";
	a.EnterInitialStat();
	cout << "\n---------------------------\n";
	cout << "LongRange Line\n";
	b.EnterInitialStat();
	cout << "\n-----------------------------\n";
	cout << "Left Flank\n";
	leftFlank.EnterInitialStat();
	cout << "\n--------------------------------\n";
	cout << "Right Flank\n";
	rightFlank.EnterInitialStat();
}
void Formation::ShowFormation()
{
	const int start = 15;

	//Show formation of LongRange
	int curLongRange = 16;
	for (int i = 0; i < 12; ++i)
	{
		gotoXY(start + 8, curLongRange++);
		for (int j = 0; j < 8; ++j)
		{
			if (b.all[i][j])
			{
				b.all[i][j]->DrawSolider();
				cout << ' ';
			}
		}
	}
	//Show formation of Front
	int curFR = curLongRange;
	for (int i = 0; i < 30; ++i)
	{
		gotoXY(start + 8,curFR++);
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
	int curFlankleft = 31;
	for (int i = 0; i < 20; ++i)
	{
		gotoXY(start, curFlankleft++);
		for (int j = 0; j < 3; ++j)
		{
			if (leftFlank.all[i][j])
			{
				leftFlank.all[i][j]->DrawSolider();
			}
		}
	}

	//show formation of right Flank
	int curFlankright = 0;
	for (int i = 0; i < 20; ++i)
	{
		gotoXY(start + 25, 30 + curFlankright++);
		for (int j = 0; j < 3; ++j)
		{
			if (rightFlank.all[i][j])
			{
				rightFlank.all[i][j]->DrawSolider();
			}
		}
	}
	
	
}

