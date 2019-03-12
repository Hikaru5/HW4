#include "stdafx.h"
#include <iostream>
#include <string>
#include "Die.h"
using namespace std;

int main()
{
	bool cont = true;
	int house=0;
	int player=0;
	Die roller(6);
	char choice;

	while (cont)
	{
		roller.roll();
		house += roller.getValue();
		roller.roll();
		house += roller.getValue();
		roller.roll();
		player += roller.getValue(); 
		roller.roll();
		player += roller.getValue();
		cout << "Your value is: " << player << "\n";
		cout << "Would you like to roll? (Y/N) ";
		cin >> choice;
		if ((choice != 'Y')||(player>=21)||(house>=21))
			cont = false;
	}

	cout << "Your value is: " << player << " and the house's value is: " << house << "\n";
	if ((player >= 21)||(house>player))
	cout << "You lost!" << endl;
	else if ((house >= 21)||(player>house))
		cout << "You win!" << endl;
	return 0;
}

