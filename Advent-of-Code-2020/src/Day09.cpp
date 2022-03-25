#include "Day09.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

Day09::Day09() : mInputFile{ "inputs/day09.txt" }
{
	cout << endl << "DAY 09" << endl;
    ReadData();
}

void Day09::Puzzle1()
{
	auto result = FindInvalidNumber();
	cout << "Puzzle 1 answer: " << result << "\n";
}

void Day09::Puzzle2()
{
	auto result = FindInvalidNumber();
	auto p = FindSubVector(result);
	auto q = std::minmax_element(mNumbers.begin() + p.first, mNumbers.begin() + p.second);

	cout << "Puzzle 2 answer: " << *q.first + *q.second << "\n";
}

long long Day09::FindInvalidNumber()
{
	const int PREAMBLE_SIZE = 25;

	mCurrentValues.clear();
	mCurrentSums.clear();

	for (size_t i = 0; i < mNumbers.size(); ++i)
	{
		auto n = mNumbers[i];
		if (i >= PREAMBLE_SIZE)
		{
			auto it = mCurrentSums.find(n);
			if (it == mCurrentSums.end())
			{
				return n;
			}

			auto toRemove = mNumbers[i - PREAMBLE_SIZE];
			for (auto v : mCurrentValues[toRemove])
			{
				auto it = mCurrentSums.find(v);
				if (it != mCurrentSums.end())
				{
					mCurrentSums.erase(it);
				}
			}
			mCurrentValues.erase(toRemove);
		}

		for (auto& v : mCurrentValues)
		{
			v.second.push_back(v.first + n);
			mCurrentSums.insert(v.first + n);
		}
		mCurrentValues.insert(make_pair(n, std::vector<long long>()));
	}
	throw std::runtime_error("Value not found");
}

std::pair<int, int> Day09::FindSubVector(const long long target)
{
	int v0 = 0, v1 = -1;
	long long acc = 0;
	while (acc != target)
	{
		if (acc < target)
		{
			acc += mNumbers[++v1];
		}
		else
		{
			acc -= mNumbers[v0++];
		}
	}
	return make_pair(v0, v1);
}

void Day09::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	string line;
	while (getline(ifs, line))
	{
		mNumbers.push_back(stoll(line));
	}
}