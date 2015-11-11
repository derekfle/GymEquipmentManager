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
		std::cout << "Equipment " << it.first << std::endl;
	}
}

void EquipmentManager::Remove(const unsigned &id)
{
	if (equipmentCache.find(id) == equipmentCache.end())
	{
		std::cout << "Equipment with id: " << id << " not found!\n";
	}
	else
	{
		equipmentCache.erase(id);
	}
}

void EquipmentManager::Add(const EquipmentType &type)
{
	// Find a unique id by searching the equipment cache
	auto GenerateId = [this]()
	{
		unsigned id = 0;
		while (true)
		{
			if (equipmentCache.find(id) == equipmentCache.end()) break;
			id++;
		}
		return id;
	};

	switch (type)
	{
	case EquipmentType::Treadmill:
		equipmentCache.insert(std::pair<unsigned, Equipment*>(GenerateId(), treadmill->Clone()));
		break;
	case EquipmentType::RowingMachine:
		equipmentCache.insert(std::pair<unsigned, Equipment*>(GenerateId(), rowingMachine->Clone()));
		break;
	default:
		std::cout << "Invalid type.\n";
	}
}
