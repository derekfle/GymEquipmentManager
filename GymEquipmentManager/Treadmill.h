/**
* Implements all treadmill functionality
*/

#pragma once

#include "Equipment.h"

class Treadmill : public Equipment
{
public:
	Treadmill();
	Treadmill(const Treadmill &that);
	~Treadmill();

	//! Clones the equipment
	virtual Equipment *Clone() const;
};

