#include <iostream>

#include "EquipmentReport.h"

EquipmentReport::EquipmentReport() :
	name(""),
	date("")
{
}

EquipmentReport::EquipmentReport(const EquipmentReport &that) :
	name(that.name),
	date(that.date)
{
}

EquipmentReport::~EquipmentReport()
{
}

void EquipmentReport::Print() const
{
	std::cout << "Member Name: " << name << std::endl;
	std::cout << "Date: " << date << std::endl;
}

std::string EquipmentReport::GetName() const
{
	return name;
}

std::string EquipmentReport::GetDate() const
{
	return date;
}
