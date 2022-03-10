#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class Day09
{
public:
	Day09();

	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();

	long long FindInvalidNumber();

	std::pair<int, int> FindSubVector(const long long target);

	std::string mInputFile;
	
	// Contains all the numbers
	std::vector<long long> mNumbers;
	
	// Contains the sums of all 25 last numbers, indexing by the first operand
	std::unordered_map<long long, std::vector<long long>> mCurrentValues;
	
	// Contains the sums of all 25 last numbers
	std::unordered_multiset<long long> mCurrentSums;
};

