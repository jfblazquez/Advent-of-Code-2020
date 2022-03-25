#include "Day10.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <array>

using namespace std;

Day10::Day10() : mInputFile{ "inputs/Day10.txt" }
{
	cout << endl << "DAY 10" << endl;
    ReadData();
}

void Day10::Puzzle1()
{
	// Adding he first and the last values
	int max = *std::max_element(mJoltages.begin(), mJoltages.end());
	mJoltages.push_back(0);
	mJoltages.push_back(max + 3);
	
	int jump1 = 0;
	int jump3 = 0;
	std::sort(mJoltages.begin(), mJoltages.end());
	for (size_t i = 1; i < mJoltages.size(); ++i)
	{
		if (mJoltages[i] - mJoltages[i - 1] == 1)
		{
			++jump1;
		}
		else if (mJoltages[i] - mJoltages[i - 1] == 3)
		{
			++jump3;
		}
	}

	cout << "Puzzle 1 answer: " << jump1 * jump3 << endl;
}

void Day10::Puzzle2()
{
	// Consider mJoltages sorted from puzzle1
	vector<long long> options(mJoltages.size(), 1);

	int size = mJoltages.size();
	for (int i = size - 3; i >= 0; --i)
	{
		int n = mJoltages[i];
		long long o = 0;
		
		if (i + 1 < size && mJoltages[i + 1] - n <= 3)
		{
			o += options[i + 1];
		}

		if (i + 2 < size && mJoltages[i + 2] - n <= 3)
		{
			o += options[i + 2];
		}

		if (i + 3 < size && mJoltages[i + 3] - n <= 3)
		{
			o += options[i + 3];
		}

		options[i] = o;
	}

	cout << "Puzzle 2 answer: " << options[0] << endl;
}

void Day10::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	for (string line; getline(ifs, line);)
	{
		mJoltages.push_back(stoi(line));
	}
}
