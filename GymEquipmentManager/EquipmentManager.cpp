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

void EquipmentManager::List() const
{
	std::cout << "/**************************************************/\n";
	for (const auto &it : equipmentCache)
	{
		if (dynamic_cast<class Treadmill*>(it.second))
		{
			std::cout << "Treadmill: ";
		}
		else
		{
			std::cout << "Rowing Machine: ";
		}
		std::cout << "[id: " << it.first << ", name: " << it.second->name << "]" << std::endl;
	}
	std::cout << "/**************************************************/\n";
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

void EquipmentManager::Add(const EquipmentType &type, const std::string &name)
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

	unsigned id;
	switch (type)
	{
	case EquipmentType::Treadmill:
		id = GenerateId();
		equipmentCache.insert(std::pair<unsigned, Equipment*>(id, treadmill->Clone()));
		break;
	case EquipmentType::RowingMachine:
		id = GenerateId();
		equipmentCache.insert(std::pair<unsigned, Equipment*>(id, rowingMachine->Clone()));
		break;
	default:
		std::cout << "Invalid type.\n";
		return;
	}

	equipmentCache.at(id)->name = name;
}
