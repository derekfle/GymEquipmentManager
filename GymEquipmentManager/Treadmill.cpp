#include "Treadmill.h"

Treadmill::Treadmill()
{
}

Treadmill::Treadmill(const Treadmill &that)
{
}

Treadmill::~Treadmill()
{
}

Equipment *Treadmill::Clone() const
{
	return new Treadmill(*this);
}
