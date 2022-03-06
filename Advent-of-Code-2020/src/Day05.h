#pragma once
#include <string>
#include <vector>

class Day05
{
public:
	Day05();

	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();

	std::string mInputFile;
	std::vector<int> mSeats;
};

