#include "Day11.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <array>

using namespace std;

Day11::Day11() : 
	mInputFile{ "inputs/day11.txt" },
	mSeatsSource{ make_unique<std::vector<std::string>>() },
	mSeatsTarget{ make_unique<std::vector<std::string>>() }
{
	cout << endl << "DAY 11" << endl;
}

void Day11::Puzzle1()
{
	ReadData();

	int changes = 0;

	do
	{
		changes = 0;
		for (int row = 0; row < mSeatsSource->size(); ++row)
		{
			for (int col = 0; col < (*mSeatsSource)[row].size(); ++col)
			{
				if (ProcessSeatWithAdjacents(row, col, mSeatsSource, mSeatsTarget))
				{
					++changes;
				}
			}
		}

		mSeatsSource.swap(mSeatsTarget);
	} while (changes > 0);	

	cout << "Puzzle 1 answer: " << CountOccupiedSeats(mSeatsTarget) << endl;
}

void Day11::Puzzle2()
{
	ReadData();

	int changes = 0;

	do
	{
		changes = 0;
		for (int row = 0; row < mSeatsSource->size(); ++row)
		{
			for (int col = 0; col < (*mSeatsSource)[row].size(); ++col)
			{
				if (ProcessSeatWithLineOfSight(row, col, mSeatsSource, mSeatsTarget))
				{
					++changes;
				}
			}
		}

		mSeatsSource.swap(mSeatsTarget);
	} while (changes > 0);

	cout << "Puzzle 1 answer: " << CountOccupiedSeats(mSeatsTarget) << endl;
}

bool Day11::ProcessSeatWithAdjacents(int row, int col,
	unique_ptr<vector<string>>& source,
	unique_ptr<vector<string>>& target)
{
	int os = AdjacentOccupiedSeats(row, col, source);
	if ((*source)[row][col] == 'L')
	{
		// Free seat
		if (os == 0)
		{
			(*target)[row][col] = '#';
			return true;
		}
	}
	else if ((*source)[row][col] == '#')
	{
		// Occupied seat
		if (os >= 4)
		{
			(*target)[row][col] = 'L';
			return true;
		}
	}

	// It doesn't change
	(*target)[row][col] = (*source)[row][col];
	return false;
}

int Day11::AdjacentOccupiedSeats(int row, int col,
	const std::unique_ptr<std::vector<std::string>>& source)
{
	int occupied = 0;
	for (int r = row - 1; r <= row + 1; ++r)
	{
		for (int c = col - 1; c <= col + 1; ++c)
		{
			if (r == row && c == col) continue;

			if (r >= 0 && r < source->size() &&
				c >= 0 && c < (*source)[r].size())
			{
				if ((*source)[r][c] == '#')
				{
					++occupied;
				}
			}
		}
	}
	return occupied;
}

bool Day11::ProcessSeatWithLineOfSight(int row, int col,
	std::unique_ptr<std::vector<std::string>>& source,
	std::unique_ptr<std::vector<std::string>>& target)
{
	int os = LineOfSightOccupied(row, col, source);
	if ((*source)[row][col] == 'L')
	{
		// Free seat
		if (os == 0)
		{
			(*target)[row][col] = '#';
			return true;
		}
	}
	else if ((*source)[row][col] == '#')
	{
		// Occupied seat
		if (os >= 5)
		{
			(*target)[row][col] = 'L';
			return true;
		}
	}

	// It doesn't change
	(*target)[row][col] = (*source)[row][col];
	return false;
}

int Day11::LineOfSightOccupied(int row, int col,
	const std::unique_ptr<std::vector<std::string>>& source)
{
	int occupied = 0;

	int r = row;
	int c = col;
	int rows = source->size();
	int cols = source->operator[](0).size();

	// To the top
	while (--r >= 0 && (*source)[r][c] == '.');
	if (r >= 0 && (*source)[r][c] == '#') ++occupied;

	// To the bottom
	r = row;
	c = col;
	while (++r < rows && (*source)[r][c] == '.');
	if (r < rows && (*source)[r][c] == '#') ++occupied;

	// To the left
	r = row;
	c = col;
	while (--c >= 0 && (*source)[r][c] == '.');
	if (c >= 0 && (*source)[r][c] == '#') ++occupied;

	// To the right
	r = row;
	c = col;
	while (++c < cols && (*source)[r][c] == '.');
	if (c < cols && (*source)[r][c] == '#') ++occupied;

	// Top-Left diagonal
	r = row;
	c = col;
	while (--r >= 0 && --c >= 0 && (*source)[r][c] == '.');
	if (r >= 0 && c >= 0 && (*source)[r][c] == '#') ++occupied;

	// Top-Right diagonal
	r = row;
	c = col;
	while (--r >= 0 && ++c < cols && (*source)[r][c] == '.');
	if (r >= 0 && c < cols && (*source)[r][c] == '#') ++occupied;

	// Bottom-Left diagonal
	r = row;
	c = col;
	while (++r < rows && --c >= 0 && (*source)[r][c] == '.');
	if (r < rows && c >= 0 && (*source)[r][c] == '#') ++occupied;

	// Bottom-Right diagonal
	r = row;
	c = col;
	while (++r < rows && ++c < cols && (*source)[r][c] == '.');
	if (r < rows && c < cols && (*source)[r][c] == '#') ++occupied;

	return occupied;
}

int Day11::CountOccupiedSeats(const unique_ptr<vector<string>>& source)
{
	int occupiedSeats = 0;
	for (int row = 0; row < source->size(); ++row)
	{
		for (int col = 0; col < (*source)[row].size(); ++col)
		{
			if ((*source)[row][col] == '#') ++occupiedSeats;
		}
	}

	return occupiedSeats;
}

void Day11::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	mSeatsSource->clear();
	mSeatsTarget->clear();
	for (string line; getline(ifs, line);)
	{
		mSeatsSource->push_back(line);
		mSeatsTarget->push_back(line);
	}
}