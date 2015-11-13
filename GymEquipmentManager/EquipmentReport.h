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

	//! Constructor
	EquipmentReport();
	//! Copy constructor
	/*!
	* \param that The object to be copied from
	*/
	EquipmentReport(const EquipmentReport &that);
	//! Destructor
	virtual ~EquipmentReport();

	//! Clones the equipment report
	//! \return The cloned report
	virtual EquipmentReport *Clone() const = 0;

	//! Prints the equipment report
	virtual void Print() const;

	//! Get the name of the member
	//! \return The name of the member
	std::string GetName() const;

	//! Get the date of the session
	//! \return The date the report was recorded
	std::string GetDate() const;

protected:

	std::string name; //!< Name of the member using equipment
	std::string date; //!< Date the report was generated
};

