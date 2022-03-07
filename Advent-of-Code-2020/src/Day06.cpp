#include "Day06.h"
#include <iostream>
#include <fstream>

using namespace std;

Day06::Day06() : mInputFile{ "inputs/day06.txt" }
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

	shared_ptr<Group> g = make_shared<Group>();
	mGroups.push_back(g);
	string line;
	while (getline(ifs, line))
	{
		if (line.empty())
		{
			g = make_shared<Group>();
			mGroups.push_back(g);
		}
		else
		{
			g->mGroupSize++;
			for (const char& c : line)
			{
				g->mYesQuestions.insert(c);
				g->mTotalYesQuestions[c]++;
			}
		}
	}
}