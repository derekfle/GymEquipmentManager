#include <ctime>
#include <chrono>
#include <fstream>
#include <iomanip> 
#include <iostream>
#include <sstream>
#include <vector>

#include "EquipmentManager.pb.h"
#include "EquipmentReportManager.h"

EquipmentReportManager::EquipmentReportManager() :
	treadmill(new TreadmillReport),
	rowingMachine(new RowingMachineReport)
{
	Load();
}

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
		std::cout << "[id: " << it.first << ", name: " << it.second->name << ", date: " << it.second->date << "]" << std::endl;
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

	Save();
}

void EquipmentReportManager::Add(const ReportType &type, const std::string &name, const std::map<std::string, unsigned> &data)
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
		dynamic_cast<TreadmillReport*>(equipmentCache.at(id))->distance = data.at("Distance");
		dynamic_cast<TreadmillReport*>(equipmentCache.at(id))->avgSpeed = data.at("AvgSpeed");
		break;
	case ReportType::RowingMachine:
		id = GenerateId();
		equipmentCache.insert(std::pair<unsigned, EquipmentReport*>(id, rowingMachine->Clone()));
		dynamic_cast<RowingMachineReport*>(equipmentCache.at(id))->duration = data.at("Duration");
		dynamic_cast<RowingMachineReport*>(equipmentCache.at(id))->repsPerMin = data.at("RepsPerMin");
		break;
	default:
		std::cout << "Invalid type.\n";
		return;
	}

	equipmentCache.at(id)->name = name;

	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	struct tm timeinfo;
	localtime_s(&timeinfo, &in_time_t);

	std::stringstream ss;
	ss << std::put_time(&timeinfo, "%Y-%m-%d");

	equipmentCache.at(id)->date = ss.str();

	Save();
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

void EquipmentReportManager::Save()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	proto::EquipmentCache cache;

	for (const auto &it : equipmentCache)
	{
		proto::Equipment *equipment = cache.add_equipment();
		equipment->set_id(it.first);
		equipment->set_name(it.second->name);
		equipment->set_date(it.second->date);
		if (dynamic_cast<TreadmillReport*>(it.second))
		{
			proto::Equipment::Treadmill *treadmill = new proto::Equipment::Treadmill; // protobuf takes ownership
			treadmill->set_avgspeed(dynamic_cast<TreadmillReport*>(it.second)->avgSpeed);
			treadmill->set_distance(dynamic_cast<TreadmillReport*>(it.second)->distance);
			equipment->set_allocated_treadmill(treadmill);
		}
		else if (dynamic_cast<RowingMachineReport*>(it.second))
		{
			proto::Equipment::RowingMachine *rowingMachine = new proto::Equipment::RowingMachine; // protobuf takes ownership
			rowingMachine->set_duration(dynamic_cast<RowingMachineReport*>(it.second)->duration);
			rowingMachine->set_repspermin(dynamic_cast<RowingMachineReport*>(it.second)->repsPerMin);
			equipment->set_allocated_rowingmachine(rowingMachine);
		}
	}

	{
		// Write the cache back to disk.
		std::fstream output("cache.dat", std::ios::out | std::ios::trunc | std::ios::binary);
		if (!cache.SerializeToOstream(&output))
		{
			std::cerr << "Failed to write cache to disk." << std::endl;
			return;
		}
	}
}

void EquipmentReportManager::Load()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	proto::EquipmentCache cache;

	// Read the existing cache
	std::fstream input("cache.dat", std::ios::in | std::ios::binary);
	if (!input)
	{
		std::cout << "File not found. Creating a new file." << std::endl;
	}
	else if (!cache.ParseFromIstream(&input))
	{
		std::cerr << "Failed to parse cache." << std::endl;
		return;
	}

	for (unsigned i = 0; i < cache.equipment_size(); i++)
	{
		if (cache.equipment(i).has_treadmill())
		{
			equipmentCache.insert(std::pair<unsigned, EquipmentReport*>(cache.equipment(i).id(), treadmill->Clone()));
			TreadmillReport *tread = dynamic_cast<TreadmillReport*>(equipmentCache.at(cache.equipment(i).id()));
			tread->avgSpeed = cache.equipment(i).treadmill().avgspeed();
			tread->distance = cache.equipment(i).treadmill().distance();
		}
		else if (cache.equipment(i).has_rowingmachine())
		{
			equipmentCache.insert(std::pair<unsigned, EquipmentReport*>(cache.equipment(i).id(), rowingMachine->Clone()));
			RowingMachineReport *rowing = dynamic_cast<RowingMachineReport*>(equipmentCache.at(cache.equipment(i).id()));
			rowing->duration = cache.equipment(i).rowingmachine().repspermin();
			rowing->repsPerMin = cache.equipment(i).rowingmachine().duration();
		}
		equipmentCache.at((unsigned)cache.equipment(i).id())->date = cache.equipment(i).date();
		equipmentCache.at((unsigned)cache.equipment(i).id())->name = cache.equipment(i).name();
	}
}
