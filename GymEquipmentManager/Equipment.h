/**
* Equipment is an abstract base class for various pieces of gym equipment.
* Any child classes should be used as prototypes
*/
#include <string>

#pragma once

class Equipment
{
public:

	friend class EquipmentManager;

	Equipment();
	virtual ~Equipment();

	//! Clones the equipment
	virtual Equipment *Clone() const = 0;

private:

	std::string name; //! Name of the equipment
};

