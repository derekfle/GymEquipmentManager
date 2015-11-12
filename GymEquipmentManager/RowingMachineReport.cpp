#include <iostream>

#include "RowingMachineReport.h"

RowingMachineReport::RowingMachineReport() :
	repsPerMin(0),
	duration(0)
{
}

RowingMachineReport::RowingMachineReport(const RowingMachineReport &that) :
	EquipmentReport(that),
	repsPerMin(that.repsPerMin),
	duration(that.duration)
{
}

RowingMachineReport::~RowingMachineReport()
{
}

EquipmentReport *RowingMachineReport::Clone() const
{
	return new RowingMachineReport(*this);
}

void RowingMachineReport::Print() const
{
	std::cout << "RowingMachine Report\n";
	std::cout << "/************/" << std::endl;
	EquipmentReport::Print();
	std::cout << "Repitions per minute: " << repsPerMin << std::endl;
	std::cout << "Duration: " << duration << std::endl;
	std::cout << "/************/" << std::endl;
}

float RowingMachineReport::GetDuration() const
{
	return duration;
}

float RowingMachineReport::GetRepsPerMin() const
{
	return repsPerMin;
}