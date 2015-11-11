#include <iostream>

#include "TreadmillReport.h"

TreadmillReport::TreadmillReport() :
	distance(0),
	avgSpeed(0)
{
}

TreadmillReport::TreadmillReport(const TreadmillReport &that) :
	EquipmentReport(that),
	distance(that.distance),
	avgSpeed(that.avgSpeed)
{
}

TreadmillReport::~TreadmillReport()
{
}

EquipmentReport *TreadmillReport::Clone() const
{
	return new TreadmillReport(*this);
}

void TreadmillReport::Print() const
{
	std::cout << "Treadmill Report\n";
	std::cout << "/************/" << std::endl;
	EquipmentReport::Print();
	std::cout << "Distance: " << distance << std::endl;
	std::cout << "Average Speed: " << avgSpeed << std::endl;
	std::cout << "/************/" << std::endl;
}
