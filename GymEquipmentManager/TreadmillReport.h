/**
* Implements all treadmill report functionality
*/

#pragma once

#include "EquipmentReport.h"

class TreadmillReport : public EquipmentReport
{
public:
	TreadmillReport();
	TreadmillReport(const TreadmillReport &that);
	~TreadmillReport();

	//! Clones the equipment report
	virtual EquipmentReport *Clone() const;

	//! Prints the equipment report
	virtual void Print() const override;
};

