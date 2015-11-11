#include <iostream>

#include "EquipmentManager.h"

std::string GetInput();

int main()
{
	EquipmentManager manager;
	char input = '\0';
	while (input != 'Q' && input != 'q')
	{
		std::cout << "Would you like to (L)ist equipment, (A)dd equipment, (R)emove equipment, or (Q)uit?\n";
		input = GetInput()[0];

		char type = '\0';
		int id = -1;
		switch (input)
		{
		case 'L':
		case 'l':
			manager.List();
			break;
		case 'A':
		case 'a':
			std::cout << "What type of equipment is this? (T)readmill or (R)owing machine: ";
			type = GetInput()[0];
			switch (type)
			{
			case 'T':
			case 't':
				std::cout << "Enter the new equipments name: ";
				manager.Add(EquipmentManager::EquipmentType::Treadmill, GetInput());
				break;
			case 'R':
			case 'r':
				std::cout << "Enter the new equipments name: ";
				manager.Add(EquipmentManager::EquipmentType::RowingMachine, GetInput());
				break;
			default:
				std::cout << "Unrecognized equipment type.\n";
				break;
			}
			break;
		case 'R':
		case 'r':
			std::cout << "Enter the ID of the equipment to be removed: ";
			std::cin >> id;
			while (std::cin.fail() || id < 0)
			{
				std::cout << "ID's must be positive integers. Try again.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> id;
			}
			manager.Remove(id);
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

std::string GetInput()
{
	std::string input;
	std::cin >> input;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return input;
}