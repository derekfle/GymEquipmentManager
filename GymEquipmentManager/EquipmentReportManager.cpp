#include <iostream>

#include "EquipmentReportManager.h"

EquipmentReportManager::EquipmentReportManager() :
	treadmill(new class TreadmillReport),
	rowingMachine(new class RowingMachineReport)
{}

EquipmentReportManager::~EquipmentReportManager()
{
	for (auto &it : equipmentCache)
	{
		delete it.second;
	}

	if (treadmill) delete treadmill;
	if (rowingMachine) delete rowingMachine;
}

void EquipmentReportManager::List() const
{
	std::cout << "/**************************************************/\n";
	for (const auto &it : equipmentCache)
	{
		if (dynamic_cast<class TreadmillReport*>(it.second))
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

void EquipmentReportManager::Remove(const unsigned &id)
{
	if (equipmentCache.find(id) == equipmentCache.end())
	{
		std::cout << "Equipment report with id: " << id << " not found!\n";
	}
	else
	{
		equipmentCache.erase(id);
	}
}

void EquipmentReportManager::Add(const ReportType &type, const std::string &name)
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
	case ReportType::Treadmill:
		id = GenerateId();
		equipmentCache.insert(std::pair<unsigned, EquipmentReport*>(id, treadmill->Clone()));
		break;
	case ReportType::RowingMachine:
		id = GenerateId();
		equipmentCache.insert(std::pair<unsigned, EquipmentReport*>(id, rowingMachine->Clone()));
		break;
	default:
		std::cout << "Invalid type.\n";
		return;
	}

	equipmentCache.at(id)->name = name;
}

void EquipmentReportManager::Print(const unsigned &id)
{
	if (equipmentCache.find(id) == equipmentCache.end())
	{
		std::cout << "Equipment report with id: " << id << " not found!\n";
	}
	else
	{
		equipmentCache.at(id)->Print();
	}
}