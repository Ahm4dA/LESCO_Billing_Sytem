#include <iostream>
#include <fstream>
#include "Menu.h"
#include <conio.h>

using namespace std;

int main()
{
	// max window func


	char choice = '=';

	cout << "Press 1 for Employee Login" << endl;
	cout << "Press 2 Customer Login" << endl;
	cout << "Press ESC to exit" << endl;
	cout << "Enter a choice : ";

	do {

		if (choice != '=')
		{
			cout << endl << "Enter the correct choice : ";
		}
		choice = _getch();

		cout << choice << endl;

	} while (choice != 49 && choice != 50 && choice != 27);

	system("cls");


	if (choice == 49)
	{
		if (EmployeeLogin())
		{
			system("cls");

		}
	}

}