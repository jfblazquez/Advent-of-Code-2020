#pragma once
#include <string>
#include <unordered_set>

class Day01
{
public:
	Day01();
	void Puzzle1();
	void Puzzle2();

private:
	
	void ReadData();

	std::string mInputFile;
	std::vector<int> mData;
	const int mTarget = 2020;
};

