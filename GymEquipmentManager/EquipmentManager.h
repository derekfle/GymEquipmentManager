/**
* EquipmentManager handles the storing, retrieving, and removing of equipment within the system. 
*/

#pragma once

#include <map>

#include "Treadmill.h"
#include "RowingMachine.h"

class EquipmentManager
{
public:

	EquipmentManager();
	~EquipmentManager();

	//! The different equipment types supported
	enum EquipmentType
	{
		Treadmill,
		RowingMachine
	};

	//! Lists all equipment in the system
	void List();

	//! Remove equipment from the system and persist new data immediately
	/*!
	* \param id The id of the equipment to be removed
	*/
	void Remove(const unsigned &id);

	//! Add equipment to the system and persist new data immediately
	/*!
	* \param type The type of the equipment to be added
	*/
	void Add(const EquipmentType &type);

private:

	std::map<unsigned, Equipment*> equipmentCache; //! Contains all of the equipment in the system
	class Treadmill *treadmill; //! treadmill prototype
	class RowingMachine *rowingMachine; //! Rowing maching prototype
};

