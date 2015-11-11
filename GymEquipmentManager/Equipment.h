/**
* Equipment is an abstract base class for various pieces of gym equipment.
* Any child classes should be used as prototypes
*/

#pragma once

class Equipment
{
public:
	Equipment();
	virtual ~Equipment();

	//! Clones the equipment
	virtual Equipment *Clone() const = 0;
};

