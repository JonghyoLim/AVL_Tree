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
	// A Z B Y C X 

	do
	{
		int option = DisplayMenu();
		string letter;
		bool found = true;

		switch (option)
		{
		case 1:
			cout << "\tEnter The itmes "<< endl;
			for (int i = 0; i < 1; i++)
			{
				//cout << "\n\t" << i+1 << " : ";
				cin >> letter;
				myTree.InsertItem(letter);
			}
			break;

		case 2:
			cout << "\tASCII CODE" << endl;
			cout << "\tA = 65, a = 97" << endl << endl;
			myTree.PrintTree();
			break;
		
		case 3:
			cout << "\tEnter a letter: ";
			cin >> letter;

			myTree.RetrieveItem(letter, found);

			if (!found) cout << "\tSorry, there is not <" << letter << "> in the tree" << endl;
			else cout << "\tYes, there is your searching letter <" << letter << "> in the tree." << endl;

			cout << "\tThe below is list of letters" << endl;
			myTree.PrintTree();
			break;

		case 4:
			cout << "\tEnter a letter: ";
			cin >> letter;
			myTree.DeleteItem(letter, found);

			if (found) 
			{
				cout << "\t<" << letter << "> in the tree so can be deleted." << endl;
			}
		

			myTree.PrintTree();
			break;

		case 5:
			cout << "\tNow, list is completely removed!" << endl;
			myTree.MakeEmpty();
			cout << "\tThe list no longer is exist." << endl;
			myTree.PrintTree();
			break;
			
		case 6:
			cout << "\tExit the application"<< endl;
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
	cout << "\t1. Insert Items.\n";
	cout << "\t2. Display the Items. \n";
	cout << "\t3. Searcing by letter. \n";
	cout << "\t4. Delete item. \n";
	cout << "\t5. Make list completely empty.\n";
	cout << "\t6. Exit from the application.\n";
	cout << "===============================================\n";

	cout << "\tPlease Enter Option---->>  ";
	cin >> option;
	system("cls");
	cout << endl << endl;

	return option;

}

