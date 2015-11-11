#include <iostream>

#include "EquipmentManager.h"

EquipmentManager::EquipmentManager() :
	treadmill(new class Treadmill),
	rowingMachine(new class RowingMachine)
{}

EquipmentManager::~EquipmentManager()
{
	for (auto &it : equipmentCache)
	{
		delete it.second;
	}

	if (treadmill) delete treadmill;
	if (rowingMachine) delete rowingMachine;
}

void EquipmentManager::List()
{
	for (const auto &it : equipmentCache)
	{
		std::cout << "Equipment\n";
	}
}

void EquipmentManager::Remove(const unsigned &id)
{
	std::cout << "Remove " << id << std::endl;
}

void EquipmentManager::Add(const EquipmentType &type)
{
	std::cout << "Add " << type << std::endl;
}
