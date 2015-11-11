/**
* Implements all rowing machine functionality
*/

#pragma once

#include "Equipment.h"

class RowingMachine : public Equipment
{
public:
	RowingMachine();
	RowingMachine(const RowingMachine &that);
	~RowingMachine();

	//! Clones the equipment
	virtual Equipment *Clone() const override;
};

