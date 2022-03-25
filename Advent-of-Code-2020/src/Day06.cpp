#include "Day06.h"
#include <iostream>
#include <fstream>

using namespace std;

Day06::Day06() : mInputFile{ "inputs/Day06.txt" }
{
	cout << endl << "DAY 06" << endl;
    ReadData();
}

void Day06::Puzzle1()
{
	long long yes = 0;
	for (const auto& g : mGroups)
	{
		yes += g->YesCount();
	}

	cout << "Puzzle 1 answer: " << yes << "\n";
}

void Day06::Puzzle2()
{
	long long allYes = 0;
	for (const auto& g : mGroups)
	{
		allYes += g->AllYesCount();
	}

	cout << "Puzzle 2 answer: " << allYes << "\n";
}

void Day06::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	mGroups.emplace_back(make_unique<Group>());
	string line;
	while (getline(ifs, line))
	{
		if (line.empty())
		{
			mGroups.emplace_back(make_unique<Group>());
		}
		else
		{
			mGroups.back()->mGroupSize++;
			for (const char& c : line)
			{
				mGroups.back()->mYesQuestions.insert(c);
				mGroups.back()->mTotalYesQuestions[c]++;
			}
		}
	}
}