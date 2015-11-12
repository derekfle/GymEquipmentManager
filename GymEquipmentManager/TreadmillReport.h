/**
* Implements all treadmill report functionality
*/

#pragma once

#include "EquipmentReport.h"

class TreadmillReport : public EquipmentReport
{
public:

	friend class EquipmentReportManager;

	//! Constructor
	TreadmillReport();
	//! Copy constructor
	/*!
	* \param that The object to be copied from
	*/
	TreadmillReport(const TreadmillReport &that);
	//! Destructor
	~TreadmillReport();

	//! Clones the equipment report
	//! \return The cloned report
	virtual EquipmentReport *Clone() const;

	//! Prints the equipment report
	virtual void Print() const override;

	//! Get the average speed during session
	//! \return The average speed
	float GetAvgSpeed() const;

	//! Get the distance travelled during session
	//! \return The distance
	float GetDistance() const;

private:

	float avgSpeed; //! The average speed for this session
	float distance; //! The distance of the session in kilometers
};
