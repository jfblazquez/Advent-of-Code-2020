#pragma once
#include <string>
#include <vector>

class Day03
{
public:
	Day03();
	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();

	std::string mInputFile;
	std::vector<std::string> mData;
};

