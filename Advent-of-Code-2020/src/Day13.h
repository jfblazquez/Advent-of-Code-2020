#pragma once
#include <string>
#include <vector>
#include <utility>

class Day13
{
public:
	Day13();
	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();

	std::string mInputFile;
	int mFrom;
	std::vector<int> mBuses;
	int mBestBus;
	int mBestDepartureTime;
};