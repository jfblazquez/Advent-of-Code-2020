#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

struct Group
{
	size_t YesCount() { return  mYesQuestions.size(); }
	size_t AllYesCount() { return std::count_if(mTotalYesQuestions.begin(), mTotalYesQuestions.end(), [&](std::pair<char, int> p) { return p.second == mGroupSize; }); }

	int mGroupSize = 0;
	std::unordered_set<char> mYesQuestions;
	std::unordered_map<char, int> mTotalYesQuestions;
};

class Day06
{
public:
	Day06();

	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();

	std::string mInputFile;
	std::vector<std::unique_ptr<Group>> mGroups;
};

