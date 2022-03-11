#pragma once
#include <string>
#include <vector>

class Day10
{
public:
	Day10();
	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();

	std::string mInputFile;
	std::vector<int> mJoltages;
};