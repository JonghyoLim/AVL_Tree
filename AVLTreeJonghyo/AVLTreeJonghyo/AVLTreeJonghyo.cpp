// AVLTreeJonghyo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "myAVL.h"
using namespace std;

bool quitFlag = false;
int DisplayMenu();

TreeType<string> myTree;
int _tmain(int argc, _TCHAR* argv[])
{
	system("color 70");
	cout << "\n\t Assignment 1\n";
	cout << "\t NAME: JONGHYO LIM\n";
	cout << "\t KNUM: K00222516\n\n\n";


	do
	{
		string name;
		int option = DisplayMenu();

		switch (option)
		{
		case 1:
			cout << "\tEnter Full name: "<< endl;
			for (int i = 0; i < 5; i++)
			{
				cout << "\n\t" << i+1 << " : ";
				cin >> name;
				 myTree.InsertItem(name);
			}
			break;

		case 2:
			cout << "\tASCII CODE" << endl;
			cout << "\tA = 65, a = 97" << endl << endl;
			myTree.PrintTree();
			break;

		case 3:
			cout << " Exit the application"<< endl;
			quitFlag = true;
		}
	} while (!quitFlag);



    return 0;
}


int DisplayMenu(void)
{
	int option;

	cout << "===============================================\n";
	cout << "\t\t AVL MENU\n";
	cout << "===============================================\n";
	cout << "\t1. Insert Items\n";
	cout << "\t2. Display the Items \n";
	cout << "\t3. Exit from the application\n";
	cout << "===============================================\n";

	cout << "\tPlease Enter Option---->>  ";
	cin >> option;
	system("cls");
	cout << endl << endl;

	return option;

}

