/**
* EquipmentManager handles the storing, retrieving, and removing of equipment reports within the system. 
*/

#pragma once

#include <map>

#include "TreadmillReport.h"
#include "RowingMachineReport.h"

class EquipmentReportManager
{
public:

	EquipmentReportManager();
	~EquipmentReportManager();

	//! The different equipment types supported
	enum ReportType
	{
		Treadmill,
		RowingMachine
	};

	//! Lists all equipment reports in the system
	void List() const;

	//! Remove equipment from the system and persist new data immediately
	/*!
	* \param id The id of the equipment report to be removed
	*/
	void Remove(const unsigned &id);

	//! Add equipment report to the system and persist new data immediately
	/*!
	* \param type The type of the equipment report to be added
	* \param name The member this report is for
	* \param data The data specific to the machine
	*/
	void Add(const ReportType &type, const std::string &name, const std::map<std::string, unsigned> &data);

	//! Remove equipment report from the system and persist new data immediately
	/*!
	* \param id The id of the equipment report to be printed
	*/
	void Print(const unsigned &id);

private:

	std::map<unsigned, EquipmentReport*> equipmentCache; //! Contains all of the equipment reports in the system
	TreadmillReport *treadmill; //! treadmill report prototype
	RowingMachineReport *rowingMachine; //! Rowing maching report prototype

	//! Saves reports to disk from the cache
	void Save();

	//! Loads reports from disk to the cache
	void Load();
};

