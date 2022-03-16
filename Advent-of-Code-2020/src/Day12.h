#pragma once
#include <string>
#include <vector>
#include <utility>

enum class FerryMovement
{
	GoNorth,
	GoSouth,
	GoEast,
	GoWest,
	Forward,
	TurnLeft,
	TurnRigth
};

struct FerryInstruction
{
	FerryInstruction(std::string mov, int value) : quantity{ value }
	{
		if (mov == "N")
		{
			move = FerryMovement::GoNorth;
		}
		else if (mov == "S")
		{
			move = FerryMovement::GoSouth;
		}
		else if (mov == "E")
		{
			move = FerryMovement::GoEast;
		}
		else if (mov == "W")
		{
			move = FerryMovement::GoWest;
		}
		else if (mov == "F")
		{
			move = FerryMovement::Forward;
		}
		else if (mov == "L")
		{
			move = FerryMovement::TurnLeft;
		}
		else if (mov == "R")
		{
			move = FerryMovement::TurnRigth;
		}

	}

	FerryMovement move;
	int quantity;
};

class Ferry
{
public:
	void ExecInstruction(FerryInstruction i);
	int lat() const { return position.second; }
	int lon() const { return position.first; }

protected:
	void virtual GoNorth(int value);
	void virtual GoSouth(int value);
	void virtual GoEast(int value);
	void virtual GoWest(int value);
	void virtual Forward(int value);
	void virtual TurnLeft(int degrees);
	void virtual TurnRigth(int degrees);

	int faceDegrees{ 0 }; // 0=East, 90=South, 180=West, 270=North 
	std::pair<int, int> position{ 0, 0 };
};

class FerryWithWaypoint : public Ferry
{
public:
	void GoNorth(int value) override;
	void GoSouth(int value) override;
	void GoEast(int value) override;
	void GoWest(int value) override;
	void Forward(int value) override;
	void TurnLeft(int degrees) override;
	void TurnRigth(int degrees) override;

private:
	std::pair<int, int> waypoint{ 10, 1 };
};

class Day12
{
public:
	Day12();
	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();
	int GetManhattanPosition(const Ferry& f);

	std::string mInputFile;
	std::vector<FerryInstruction> mInstructions;
};