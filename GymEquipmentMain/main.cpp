#include <iostream>

#include "EquipmentManager.h"

int main()
{
	EquipmentManager manager;
	char input = '\0';
	while (input != 'Q' && input != 'q')
	{
		std::cout << "Would you like to (L)ist equipment, (A)dd equipment, (R)emove equipment, or (Q)uit?\n";
		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (input)
		{
		case 'L':
		case 'l':
			manager.List();
			break;
		case 'A':
		case 'a':
			manager.Add(EquipmentManager::EquipmentType::Treadmill);
			break;
		case 'R':
		case 'r':
			manager.Remove(1);
			break;
		case 'Q':
		case 'q':
			std::cout << "Shutting down...\n";
			break;
		default:
			std::cout << "Unrecognized command.\n";
			break;
		}
	}
}