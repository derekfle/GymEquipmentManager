/**
* EquipmentReport is an abstract base class for equipment reports.
* Any child classes should be used as prototypes
*/
#include <string>

#pragma once

class EquipmentReport
{
public:

	friend class EquipmentReportManager;

	EquipmentReport();
	EquipmentReport(const EquipmentReport &that);
	virtual ~EquipmentReport();

	//! Clones the equipment report
	virtual EquipmentReport *Clone() const = 0;

	//! Prints the equipment report
	virtual void Print() const;

private:

	std::string name; //! Name of the member using equipment
	std::string date; //! Date the report was generated
};

