/**
* Implements all treadmill report functionality
*/

#pragma once

#include "EquipmentReport.h"

class TreadmillReport : public EquipmentReport
{
public:

	friend class EquipmentReportManager;

	TreadmillReport();
	//! Copy constructor
	/*!
	* \param that The object to be copied from
	*/
	TreadmillReport(const TreadmillReport &that);
	~TreadmillReport();

	//! Clones the equipment report
	virtual EquipmentReport *Clone() const;

	//! Prints the equipment report
	virtual void Print() const override;

private:

	float avgSpeed; //! The average speed for this session
	float distance; //! The distance of the session in kilometers
};

