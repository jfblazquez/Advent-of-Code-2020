#pragma once
#include <string>
#include <vector>
#include <memory>

class Day11
{
public:
	Day11();
	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();
	
	bool ProcessSeatWithAdjacents(int row, int col,
		std::unique_ptr<std::vector<std::string>>& source,
		std::unique_ptr<std::vector<std::string>>& target);

	int AdjacentOccupiedSeats(int row, int col,
		const std::unique_ptr<std::vector<std::string>>& source);

	bool ProcessSeatWithLineOfSight(int row, int col,
		std::unique_ptr<std::vector<std::string>>& source,
		std::unique_ptr<std::vector<std::string>>& target);

	int LineOfSightOccupied(int row, int col,
		const std::unique_ptr<std::vector<std::string>>& source);

	int CountOccupiedSeats(const std::unique_ptr<std::vector<std::string>>& source);

	std::string mInputFile;
	std::unique_ptr<std::vector<std::string>> mSeatsSource;
	std::unique_ptr<std::vector<std::string>> mSeatsTarget;
};