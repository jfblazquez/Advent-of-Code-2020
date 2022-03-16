#include "Day12.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <regex>

using namespace std;

Day12::Day12() : mInputFile{ "inputs/day12.txt" }
{
	cout << endl << "DAY 12" << endl;
    ReadData();
}

void Day12::Puzzle1()
{
	Ferry ferry;
	for (const auto& inst : mInstructions)
	{
		ferry.ExecInstruction(inst);
	}

	cout << "Puzzle 1 answer: " << GetManhattanPosition(ferry) << endl;
}

void Day12::Puzzle2()
{
	FerryWithWaypoint ferry;
	for (const auto& inst : mInstructions)
	{
		ferry.ExecInstruction(inst);
	}

	cout << "Puzzle 2 answer: " << GetManhattanPosition(ferry) << endl;
}

int Day12::GetManhattanPosition(const Ferry& f)
{
	return abs(f.lat()) + abs(f.lon());
}

void Day12::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	regex r{ "([A-Z]{1})([0-9]+)" };
	smatch m;
	for (string line; getline(ifs, line);)
	{
		if (regex_match(line, m, r))
		{
			string mov = m[1];
			int value = stoi(m[2]);
			mInstructions.push_back(FerryInstruction(mov, value));
		}
	}
}

void Ferry::ExecInstruction(FerryInstruction i)
{
	switch (i.move)
	{
	case FerryMovement::GoNorth:
		GoNorth(i.quantity);
		break;
	case FerryMovement::GoSouth:
		GoSouth(i.quantity);
		break;
	case FerryMovement::GoEast:
		GoEast(i.quantity);
		break;
	case FerryMovement::GoWest:
		GoWest(i.quantity);
		break;
	case FerryMovement::Forward:
		Forward(i.quantity);
		break;
	case FerryMovement::TurnLeft:
		TurnLeft(i.quantity);
		break;
	case FerryMovement::TurnRigth:
		TurnRigth(i.quantity);
		break;
	default:
		break;
	}
}

void Ferry::GoNorth(int value)
{
	position.second += value;
}

void Ferry::GoSouth(int value)
{
	position.second -= value;
}

void Ferry::GoEast(int value)
{
	position.first += value;
}

void Ferry::GoWest(int value)
{
	position.first -= value;
}

void Ferry::Forward(int value)
{
	switch (faceDegrees)
	{
	case 0:
		GoEast(value);
		break;
	case 90:
		GoSouth(value);
		break;
	case 180:
		GoWest(value);
		break;
	case 270:
		GoNorth(value);
		break;
	default:
		cout << "Problema\n";
		break;
	}
}

void Ferry::TurnLeft(int degrees)
{
	faceDegrees -= degrees;
	while (faceDegrees < 0) faceDegrees += 360;
}

void Ferry::TurnRigth(int degrees)
{
	faceDegrees += degrees;
	while (faceDegrees >= 360) faceDegrees -= 360;
}

void FerryWithWaypoint::GoNorth(int value)
{
	waypoint.second += value;
}

void FerryWithWaypoint::GoSouth(int value)
{
	waypoint.second -= value;
}

void FerryWithWaypoint::GoEast(int value)
{
	waypoint.first += value;
}

void FerryWithWaypoint::GoWest(int value)
{
	waypoint.first -= value;
}

void FerryWithWaypoint::Forward(int value)
{
	position.first += value * waypoint.first;
	position.second += value * waypoint.second;
}

void FerryWithWaypoint::TurnLeft(int degrees)
{
	while (degrees > 0)
	{
		int x = waypoint.first;
		int y = waypoint.second;
		waypoint.first = -y;
		waypoint.second = x;
		degrees -= 90;
	}
}

void FerryWithWaypoint::TurnRigth(int degrees)
{
	while (degrees > 0)
	{
		int x = waypoint.first;
		int y = waypoint.second;
		waypoint.first = y;
		waypoint.second = -x;
		degrees -= 90;
	}
}