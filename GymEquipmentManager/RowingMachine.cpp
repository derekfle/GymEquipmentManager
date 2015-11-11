#include "RowingMachine.h"

RowingMachine::RowingMachine()
{
}

RowingMachine::RowingMachine(const RowingMachine &that)
{
}

RowingMachine::~RowingMachine()
{
}

Equipment *RowingMachine::Clone() const
{
	return new RowingMachine(*this);
}
