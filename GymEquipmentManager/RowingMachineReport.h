/**
* Implements all rowing machine report functionality
*/

#pragma once

#include "EquipmentReport.h"

class RowingMachineReport : public EquipmentReport
{
public:

	friend class EquipmentReportManager;

	RowingMachineReport();
	//! Copy constructor
	/*!
	* \param that The object to be copied from
	*/
	RowingMachineReport(const RowingMachineReport &that);
	~RowingMachineReport();

	//! Clones the equipment report
	virtual EquipmentReport *Clone() const override;

	//! Prints the equipment report
	virtual void Print() const override;

private:

	float duration; //! The duration of the session in seconds
	float repsPerMin; //! The rows per minuts of the session
};

