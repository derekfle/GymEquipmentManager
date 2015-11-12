/**
* Test cases for the equipment report management system
*/

#include <chrono>
#include <fstream>

#include "EquipmentManager.pb.h"
#include "EquipmentReportManager.h"
#include "gtest/gtest.h"


class EquipmentReportManagerTest : public ::testing::Test
{
protected:

	static void SetUpTestCase()
	{
		std::ifstream f("cache.dat");
		if (f.good())
		{
			f.close();
			FAIL(); // Cache already exists!
		}
	}

	static void TearDownTestCase() // Tear down only after ALL tests ran
	{
		// Remove the cache file so next tests starts clean
		std::remove("cache.dat");
	}
};

// Add several reports and confirm their existence on disk
TEST_F(EquipmentReportManagerTest, AddReports) 
{
	EquipmentReportManager manager;

	// Add a treadmill
	{
		std::map<std::string, unsigned> data;
		data.insert(std::pair<std::string, unsigned>("AvgSpeed", 30));
		data.insert(std::pair<std::string, unsigned>("Distance", 10));
		manager.Add(EquipmentReportManager::ReportType::Treadmill, "Bob", data);
	}

	// Add a rowing machine
	{
		std::map<std::string, unsigned> data;
		data.insert(std::pair<std::string, unsigned>("Duration", 60));
		data.insert(std::pair<std::string, unsigned>("RepsPerMin", 12));
		manager.Add(EquipmentReportManager::ReportType::RowingMachine, "Doug", data);
	}

	EXPECT_EQ(manager.Num(), 2);

	proto::EquipmentCache cache;
	{
		// Read the existing cache
		std::fstream input("cache.dat", std::ios::in | std::ios::binary);
		ASSERT_TRUE(cache.ParseFromIstream(&input));
	}
	EXPECT_EQ(cache.equipment_size(), 2);

	// Get the current date
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	struct tm timeinfo;
	localtime_s(&timeinfo, &in_time_t);

	std::stringstream ss;
	ss << std::put_time(&timeinfo, "%Y-%m-%d");

	for (unsigned i = 0; i < cache.equipment_size(); i++)
	{
		if (cache.equipment(i).has_treadmill())
		{
			EXPECT_EQ(cache.equipment(i).treadmill().avgspeed(), 30);
			EXPECT_EQ(cache.equipment(i).treadmill().distance(), 10);
			EXPECT_STREQ(cache.equipment(i).name().c_str(), "Bob");
			EXPECT_STREQ(cache.equipment(i).date().c_str(), ss.str().c_str());
		}
		else if (cache.equipment(i).has_rowingmachine())
		{
			EXPECT_EQ(cache.equipment(i).rowingmachine().repspermin(), 12);
			EXPECT_EQ(cache.equipment(i).rowingmachine().duration(), 60);
			EXPECT_STREQ(cache.equipment(i).name().c_str(), "Doug");
			EXPECT_STREQ(cache.equipment(i).date().c_str(), ss.str().c_str());
		}
	}
}

// Test that reports are reloaded into the report manager on instantiation
TEST_F(EquipmentReportManagerTest, PersistReports)
{
	EquipmentReportManager manager;
	EXPECT_EQ(manager.Num(), 2);

	proto::EquipmentCache cache;
	{
		// Read the existing cache
		std::fstream input("cache.dat", std::ios::in | std::ios::binary);
		ASSERT_TRUE(cache.ParseFromIstream(&input));
	}
	EXPECT_EQ(cache.equipment_size(), 2);

	for (unsigned i = 0; i < cache.equipment_size(); i++)
	{
		if (cache.equipment(i).has_treadmill())
		{
			EquipmentReport *report = manager.GetReportAtId(cache.equipment(i).id());
			EXPECT_EQ(cache.equipment(i).treadmill().avgspeed(), dynamic_cast<TreadmillReport*>(report)->GetAvgSpeed());
			EXPECT_EQ(cache.equipment(i).treadmill().distance(), dynamic_cast<TreadmillReport*>(report)->GetDistance());
			EXPECT_STREQ(cache.equipment(i).name().c_str(), report->GetName().c_str());
			delete report;
		}
		else if (cache.equipment(i).has_rowingmachine())
		{
			EquipmentReport *report = manager.GetReportAtId(cache.equipment(i).id());
			EXPECT_EQ(cache.equipment(i).rowingmachine().duration(), dynamic_cast<RowingMachineReport*>(report)->GetDuration());
			EXPECT_EQ(cache.equipment(i).rowingmachine().repspermin(), dynamic_cast<RowingMachineReport*>(report)->GetRepsPerMin());
			EXPECT_STREQ(cache.equipment(i).name().c_str(), report->GetName().c_str());;
			delete report;
		}
	}
}

// Remove reports added in first test and confirm they no longer exist on disk
TEST_F(EquipmentReportManagerTest, RemoveReports)
{
	EquipmentReportManager manager;
	EXPECT_EQ(manager.Num(), 2);

	proto::EquipmentCache cache;
	{
		// Read the existing cache
		std::fstream input("cache.dat", std::ios::in | std::ios::binary);
		ASSERT_TRUE(cache.ParseFromIstream(&input));
	}
	EXPECT_EQ(cache.equipment_size(), 2);

	for (unsigned i = 0; i < cache.equipment_size(); i++)
	{
		manager.Remove(cache.equipment(i).id());
	}

	EXPECT_EQ(manager.Num(), 0);
	{
		// Read the existing cache
		std::fstream input("cache.dat", std::ios::in | std::ios::binary);

		ASSERT_TRUE(cache.ParseFromIstream(&input));
		EXPECT_EQ(cache.equipment_size(), 0);
	}
}

// Test cloning reports
TEST(EquipmentReportTest, CloneTest)
{
	EquipmentReportManager manager;

	// Add a treadmill
	{
		std::map<std::string, unsigned> data;
		data.insert(std::pair<std::string, unsigned>("AvgSpeed", 30));
		data.insert(std::pair<std::string, unsigned>("Distance", 10));
		manager.Add(EquipmentReportManager::ReportType::Treadmill, "Bob", data);
	}

	// Add a rowing machine
	{
		std::map<std::string, unsigned> data;
		data.insert(std::pair<std::string, unsigned>("Duration", 60));
		data.insert(std::pair<std::string, unsigned>("RepsPerMin", 12));
		manager.Add(EquipmentReportManager::ReportType::RowingMachine, "Doug", data);
	}

	std::vector<EquipmentReport*> reports = manager.GetReports();
	for (EquipmentReport *it : reports)
	{
		EquipmentReport *tmpReport = it->Clone();

		if (dynamic_cast<RowingMachineReport*>(tmpReport))
		{
			EXPECT_EQ(dynamic_cast<RowingMachineReport*>(tmpReport)->GetDuration(), dynamic_cast<RowingMachineReport*>(it)->GetDuration());
			EXPECT_EQ(dynamic_cast<RowingMachineReport*>(tmpReport)->GetRepsPerMin(), dynamic_cast<RowingMachineReport*>(it)->GetRepsPerMin());
		}
		else if (dynamic_cast<TreadmillReport*>(tmpReport))
		{
			EXPECT_EQ(dynamic_cast<TreadmillReport*>(tmpReport)->GetDistance(), dynamic_cast<TreadmillReport*>(it)->GetDistance());
			EXPECT_EQ(dynamic_cast<TreadmillReport*>(tmpReport)->GetAvgSpeed(), dynamic_cast<TreadmillReport*>(it)->GetAvgSpeed());
		}

		EXPECT_EQ(tmpReport->GetName(), it->GetName());
		EXPECT_EQ(tmpReport->GetDate(), it->GetDate());

		delete tmpReport;
	}

	for (EquipmentReport *it : reports)
	{
		delete it;
	}
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE"); // Nasty...
}