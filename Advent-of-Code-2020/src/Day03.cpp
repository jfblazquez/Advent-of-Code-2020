#include "Day03.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>

using namespace std;

Day03::Day03() : mInputFile{ "inputs/day03.txt" }
{
	cout << endl << "DAY 03" << endl;
    ReadData();
}

void Day03::Puzzle1()
{
	int x = 0, y = 0;
	int width = mData[0].size();
	int height = mData.size();
	int trees = 0;
	while (y < height)
	{
		if (mData[y][x] == '#')
		{
			++trees;
		}

		x = (x + 3) % width;
		++y;
	}

	cout << "Puzzle 1 answer: " << trees << endl;
}

void Day03::Puzzle2()
{
	struct slope
	{
		slope(int xm, int ym) : x_move{xm}, y_move{ym} {}

		int x = 0;
		int y = 0;
		int x_move;
		int y_move;
		int trees = 0;
	};

	vector<slope> slopes{ slope{1,1}, slope{3,1}, slope{5,1}, slope{7,1}, slope{1,2} };

	int width = mData[0].size();
	int height = mData.size();
	while (true)
	{
		for (slope& s : slopes)
		{
			if (s.y < height)
			{
				if (mData[s.y][s.x] == '#')
				{
					++s.trees;
				}
				s.x = (s.x + s.x_move) % width;
				s.y += s.y_move;
			}
		}

		if (std::all_of(slopes.begin(), slopes.end(), [height](slope& s) {return s.y >= height; }))
		{
			break;
		}
	}

	long long trees = 1;
	for (slope& s : slopes)
	{
		trees *= s.trees;
	}
	cout << "Puzzle 2 answer: " << trees << endl;
}

void Day03::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	string line;
	while (getline(ifs, line))
	{
		mData.push_back(line);
	}
}
