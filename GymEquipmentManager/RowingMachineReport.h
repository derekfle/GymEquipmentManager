/**
* Implements all rowing machine report functionality
*/

#pragma once

#include "EquipmentReport.h"

class RowingMachineReport : public EquipmentReport
{
public:

	friend class EquipmentReportManager;

	//! Constructor
	RowingMachineReport();
	//! Copy constructor
	/*!
	* \param that The object to be copied from
	*/
	RowingMachineReport(const RowingMachineReport &that);
	//! Destructor
	~RowingMachineReport();

	//! Clones the equipment report
	//! \return The cloned report
	virtual EquipmentReport *Clone() const override;

	//! Prints the equipment report
	virtual void Print() const override;

	//! Get the duration of the session
	//! \return The duration
	float GetDuration() const;

	//! Get the repititions per minute of the session
	//! \return The repitions per minute
	float GetRepsPerMin() const;

private:

	float duration; //! The duration of the session in seconds
	float repsPerMin; //! The rows per minuts of the session
};

