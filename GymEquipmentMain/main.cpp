/**
* A wrapper for the equipment report manager to demonstrate use
*/

#include <iostream>

#include "EquipmentReportManager.h"

std::string GetInput();
unsigned GetInputUnsigned();

int main()
{
	EquipmentReportManager manager;
	char input = '\0';
	while (input != 'Q' && input != 'q')
	{
		std::cout << "Would you like to (L)ist reports, (A)dd a report, (R)emove a report, (P)rint report, or (Q)uit?\n";
		input = GetInput()[0];

		char type = '\0';
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
				std::cout << "Enter the name of the member: ";
				manager.Add(EquipmentReportManager::ReportType::Treadmill, GetInput());
				break;
			case 'R':
			case 'r':
				std::cout << "Enter the name of the member: ";
				manager.Add(EquipmentReportManager::ReportType::RowingMachine, GetInput());
				break;
			default:
				std::cout << "Unrecognized equipment type.\n";
				break;
			}
			break;
		case 'R':
		case 'r':
			std::cout << "Enter the ID of the equipment report to be removed: ";
			manager.Remove(GetInputUnsigned());
			break;
		case 'P':
		case 'p':
			std::cout << "Enter the ID of the equipment report to be printed: ";
			manager.Print(GetInputUnsigned());
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

unsigned GetInputUnsigned()
{
	int input = -1;

	std::cin >> input;
	while (std::cin.fail() || input < 0)
	{
		std::cout << "Please enter a positive integer. Try again.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}

	return input;
}